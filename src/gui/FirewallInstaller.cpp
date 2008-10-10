/*

                          Firewall Builder

                 Copyright (C) 2008 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@fwbuilder.org

  $Id$

  This program is free software which we release under the GNU General Public
  License. You may redistribute and/or modify this program under the terms
  of that license as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  To get a copy of the GNU General Public License, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "../../config.h"
#include "global.h"
#include "utils.h"
#include "utils_no_qt.h"

#include "FirewallInstaller.h"
#include "instDialog.h"
#include "FWBSettings.h"
#include "FWWindow.h"
#include "SSHSession.h"

#include "fwbuilder/Resources.h"
#include "fwbuilder/FWObjectDatabase.h"
#include "fwbuilder/Firewall.h"
#include "fwbuilder/XMLTools.h"
#include "fwbuilder/Interface.h"
#include "fwbuilder/Management.h"

#include <qdir.h>
#include <qfileinfo.h>
#include <qstring.h>

#ifndef _WIN32
#  include <unistd.h>     // for access(2) and getdomainname
#endif

#include <errno.h>
#include <iostream>

using namespace std;
using namespace libfwbuilder;

bool FirewallInstaller::packInstallJobsList(Firewall*)
{
    return false;
}

void FirewallInstaller::packSSHArgs(QStringList &args)
{
    QString ssh = st->getSSHPath();

#ifdef _WIN32
    args.push_back(ssh);
/*
 * putty ignores protocol and port specified in the session file if
 * command line option -ssh is given.
 *
 * On the other hand,the sign of session usage is an empty user name,
 * so we can check for that. If user name is empty, then putty will
 * use current Windows account name to log in to the firewall and this
 * is unlikely to work anyway. This seems to be a decent workaround.
 */
    if (!cnf->user.isEmpty() && ssh.toLower().indexOf("plink.exe")!=-1)
    {
        args.push_back("-ssh");
        args.push_back("-pw");
        args.push_back(cnf->pwd);
    }

#else

    args.push_back(argv0.c_str());
    args.push_back("-X");   // fwbuilder works as ssh wrapper
    //if (fwbdebug)
    //    args.push_back("-d");
    args.push_back("-t");
    args.push_back("-t");

#endif

    if (!cnf->sshArgs.isEmpty())
        args += cnf->sshArgs.split(" ", QString::SkipEmptyParts);
    if (cnf->verbose) args.push_back("-v");
    if (!cnf->user.isEmpty())
    {
        args.push_back("-l");
        args.push_back(cnf->user);
        args.push_back(cnf->maddr);
    } else
        args.push_back(cnf->maddr);
}

void FirewallInstaller::packSCPArgs(const QString &file_name,
                                    QStringList &args)
{
    QString file_with_path = getFullPath(file_name);
    QString scp = st->getSCPPath();

#ifdef _WIN32
    args.push_back(scp);

    if (!cnf->user.isEmpty() && scp.toLower().indexOf("pscp.exe")!=-1)
    {
//        args.push_back("-ssh");
        args.push_back("-pw");
        args.push_back(cnf->pwd);
    }

#else
    args.push_back(argv0.c_str());
    args.push_back("-Y");   // fwbuilder works as scp wrapper
#endif

    if (!cnf->scpArgs.isEmpty())
        args += cnf->scpArgs.split(" ", QString::SkipEmptyParts);

    args.push_back("-q");

    args.push_back(file_with_path);

    if (!cnf->user.isEmpty())
        args.push_back(cnf->user + "@" + cnf->maddr + ":" + cnf->fwdir);
    else
        args.push_back(cnf->maddr + ":" + cnf->fwdir);
}

/*
 * take next job from job_list and execute it
 */
void FirewallInstaller::runJobs()
{
    if (fwbdebug) qDebug("FirewallInstaller::runJobs");
    if (job_list.size()==0)
    {
        if (fwbdebug) qDebug("FirewallInstaller::runJobs:  job list is empty");
        QTimer::singleShot( 1000, this, SLOT(mainLoopInstall()));
        return;
    }

    instJob current_job = job_list.front();
    job_list.pop_front();

    switch (current_job.job) 
    {
    case COPY_FILE:
        copyFile(current_job.argument);
        break;

    case EXECUTE_COMMAND:
        executeCommand(current_job.argument);
        break;

    case ACTIVATE_POLICY:
        activatePolicy();
        break;
    }
}

/*
 * copyFile starts background process and returns. Process object
 * emits signal finished() which will be connected to slot
 * commandFinished(). This slot checks termination status of the process
 * and if it was successfull, it schedules call to runJobs()
 */
void FirewallInstaller::copyFile(const QString &file_name)
{
}

void FirewallInstaller::executeCommand(const QString &cmd)
{
}    

void FirewallInstaller::activatePolicy()
{
    QTimer::singleShot( 0, this, SLOT(runJobs()));
}    

/*
 * parameter intermediate: if true, then this session is part of the
 * set required to complete install on single firewall, such as when
 * we need to copy several files and then activate policy. If this
 * parameter is false, the session is final and installer terminates
 * when it finishes. This only applies to when session finishes
 * successfully. If session finishes with an error, we always
 * terminate installer.
 */
void FirewallInstaller::runSSHSession(SSHSession *s, bool intermediate)
{
    if (fwbdebug) qDebug("FirewallInstaller::runSSHSession()");

    session = s;

    session->setOptions(cnf);
    session->setFWBPrompt(fwb_prompt);

    connect(session,SIGNAL(printStdout_sign(const QString&)),
            inst_dlg, SLOT(addToLog(const QString&)));

    if (intermediate)
        connect(session,SIGNAL(sessionFinished_sign()),
                this, SLOT(runJobs()));
    else
        connect(session,SIGNAL(sessionFinished_sign()),
                inst_dlg, SLOT(installerSuccess()));

    connect(session,SIGNAL(sessionFatalError_sign()),
            inst_dlg, SLOT(installerError()));

    connect(session,SIGNAL(updateProgressBar_sign(int,bool)),
            inst_dlg, SLOT(updateProgressBar(int,bool)));

    session->startSession();
}

QString FirewallInstaller::getFullPath(const QString &file )
{
    if (QDir::isRelativePath(file)) return cnf->wdir + "/" + file;
    else return file;
}

/*
 * This method builds and returns activation command
 * This method is used for all firewall platforms but PIX
 */
QString FirewallInstaller::getActivationCmd()
{
    if (!cnf->activationCmd.isEmpty())
    {
        return cnf->activationCmd;
    }

    QString cmd="";

    string optpath="activation/";

    if (cnf->user=="root") optpath += "root/";
    else                   optpath += "reg_user/";

    if (cnf->testRun)
    {
        optpath += "test/";
        if (cnf->rollback) optpath += "rollback/";
        else               optpath += "no_rollback/";
    } else
    {
        optpath += "run/";
        if (cnf->compressScript) optpath += "compression/";
        else                     optpath += "no_compression/";
    }

    cmd = Resources::getTargetOptionStr(cnf->fwobj->getStr("host_OS"),
                                        optpath).c_str();
    return inst_dlg->replaceMacrosInCommand(cmd);
}

QString FirewallInstaller::getGeneratedFileFullPath(Firewall *fw)
{
/* bug #1617501: "Install fails after compile". The "output file"
 * setting that user enters in the "Compiler" tab of fw advanced
 * dialog can be either local or absolute path. 
 */
    FWOptions  *fwopt = fw->getOptionsObject();
    QString generated_file;
    QString ofname = QString::fromUtf8(fwopt->getStr("output_file").c_str());
    if (!ofname.isEmpty())
        generated_file = ofname;
    else
        generated_file = QString::fromUtf8(fw->getName().c_str()) + ".fw";

    QFileInfo gen_file_info(generated_file);
    if (!gen_file_info.isAbsolute())
    {
        QFileInfo fwb_file_info = QFileInfo(mw->getRCS()->getFileName());
        generated_file = fwb_file_info.dir().path() + "/" + generated_file;
    }
    return QDir::toNativeSeparators(generated_file);
}
 
