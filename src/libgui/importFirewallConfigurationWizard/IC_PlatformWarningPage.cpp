/*

                          Firewall Builder

                 Copyright (C) 2011 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@fwbuilder.org

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


#include "global.h"

#include "IC_PlatformWarningPage.h"
#include "ImportFirewallConfigurationWizard.h"

#include <QString>
#include <QFile>
#include <QRegExp>
#include <QTextStream>


IC_PlatformWarningPage::IC_PlatformWarningPage(QWidget *parent) : QWizardPage(parent)
{
    m_dialog = new Ui::IC_PlatformWarningPage_q;
    m_dialog->setupUi(this);

    setField("platform", "");

    platformOk = false;
}

bool IC_PlatformWarningPage::isComplete() const
{
    return platformOk;
}

void IC_PlatformWarningPage::initializePage()
{
    QString fileName = field("fileName").toString();

    QFile cf(fileName);
    if (cf.open(QIODevice::ReadOnly ))
    {
        QList<QRegExp> pix_re;
        pix_re << QRegExp("^ASA Version")
               << QRegExp("^PIX Version")
               << QRegExp("^FWSM Version")
               << QRegExp("^nat \\(\\S+,\\S+\\)")
               << QRegExp("^static \\(\\S+,\\S+\\)")
               << QRegExp("^global \\(")
               << QRegExp("^nameif \\S+")
               << QRegExp("^fixup \\S+");

        QList<QRegExp> fwsm_re;
        fwsm_re << QRegExp("^FWSM Version");

        QList<QRegExp> ios_re;
        ios_re << QRegExp("IOS Version")
               << QRegExp("^[vV]ersion 1[012]\\..*");

        QList<QRegExp> iptables_re;
        iptables_re << QRegExp("# Generated by iptables-save")
                    << QRegExp("^:INPUT ")
                    << QRegExp("^:OUTPUT ")
                    << QRegExp("^:FORWARD ")
                    << QRegExp("^-A INPUT ")
                    << QRegExp("^-A OUTPUT ")
                    << QRegExp("^-A FORWARD ");
            
        QList<QRegExp> iptables_with_counters_re;
        iptables_with_counters_re << QRegExp("^\\[\\d+:\\d+\\] -A INPUT ")
                                  << QRegExp("^\\[\\d+:\\d+\\] -A OUTPUT ")
                                  << QRegExp("^\\[\\d+:\\d+\\] -A FORWARD ");

        QList<QRegExp> pf_conf_re;
        pf_conf_re << QRegExp("^scrub\\s+\\S+")
                   << QRegExp("^set\\s+timeout\\s+\\S+")
                   << QRegExp("^pass\\s+")
                   << QRegExp("^block\\s+")
                   << QRegExp("^nat\\s+(?!\\()")
                   << QRegExp("^rdr\\s+(?!\\()")
                   << QRegExp("^table\\s+<\\S+>\\s+");

        m_dialog->configFileBrowser->clear();
        m_dialog->platform->setText(tr("Unknown"));

        QStringList *buf = 
            dynamic_cast<ImportFirewallConfigurationWizard*>(wizard())->
            getBufferPtr();

        QTextStream stream(&cf);
        while (true)
        {
            QString line = stream.readLine().trimmed();
            if (line.isNull()) break;
            m_dialog->configFileBrowser->append(line);
            *buf << line;
        }

        bool iptables_c = false;

        foreach (QString line, *buf)
        {
            if (detectedPlatform.isEmpty())
            {
                foreach (QRegExp re, pix_re)
                {
                    if (re.indexIn(line) > -1)
                    {
                        detectedPlatform = "pix";
                        break;
                    }
                }

                foreach (QRegExp re, fwsm_re)
                {
                    if (re.indexIn(line) > -1)
                    {
                        detectedPlatform = "fwsm";
                        break;
                    }
                }

                foreach (QRegExp re, ios_re)
                {
                    if (re.indexIn(line) > -1)
                    {
                        detectedPlatform = "iosacl";
                        break;
                    }
                }

                foreach (QRegExp re, iptables_re)
                {
                    if (re.indexIn(line) > -1)
                    {
                        detectedPlatform = "iptables";
                        break;
                    }
                }

                foreach (QRegExp re, pf_conf_re)
                {
                    if (re.indexIn(line) > -1)
                    {
                        detectedPlatform = "pf";
                        break;
                    }
                }
            }

            if (detectedPlatform == "iptables")
            {
                foreach (QRegExp re, iptables_with_counters_re)
                {
                    if (re.indexIn(line) > -1)
                    {
                        iptables_c = true;
                        break;
                    }
                }
            }
        }

        QTextCursor cursor = m_dialog->configFileBrowser->textCursor();
        cursor.setPosition(0, QTextCursor::MoveAnchor);
        m_dialog->configFileBrowser->setTextCursor(cursor);
        m_dialog->configFileBrowser->ensureCursorVisible();

        if (detectedPlatform.isEmpty())
        {
            m_dialog->platform->setText(tr("Unknown"));
            m_dialog->platformSpecificWarning->setText(
                tr("Unrecognized configuration file format, can not import."));
            platformOk = false;
        }

        if (detectedPlatform == "pix" || detectedPlatform == "fwsm")
        {
            m_dialog->platform->setText(tr("Cisco PIX / CIsco ASA / Cisco FWSM"));
            m_dialog->platformSpecificWarning->setText(
                tr("Not all Cisco ASA and PIX configuration commands are "
                   "supported by Firewall Builder. "
                   "The following configuration components will be imported "
                   "and can be managed using "
                   "Firewall Builder:"
                   "<ul>"
                   "<li>Interface configurations (IP address, security level, "
                   "name, etc.)</li>"
                   "<li>Access lists</li>"
                   "<li>Static routes [if we decide to support this]</li>"
                   "</ul>"
                   "The following configuration components will not be imported:"
                   "<ul>"
                   "<li>VPN</li>"
                   "<li>Dynamic routing protocols</li>"
                   "<li>QoS</li>"
                   "</ul>"
                ));
            platformOk = true;
        }

        if (detectedPlatform == "iosacl")
        {
            m_dialog->platform->setText(tr("Cisco Router IOS"));
            m_dialog->platformSpecificWarning->setText(
                tr("Not all Cisco IOS configuration commands are "
                   "supported by Firewall Builder. The following "
                   "configuration components will be imported and "
                   "can be managed using Firewall Builder:"
                   "<ul>"
                   "<li>Interface configurations (IP address)</li>"
                   "<li>Extended access lists</li>"
                   "</ul>"
                   "The following configuration components will not be imported:"
                   "<ul>"
                   "<li>VPN</li>"
                   "<li>Static routes</li>"
                   "<li>Dynamic routing protocols (OSPF, RIP, etc.)</li>"
                   "<li>QoS</li>"
                   "</ul>"
                ));
            platformOk = true;
        }

        if (detectedPlatform == "iptables")
        {
            m_dialog->platform->setText(tr("iptables"));
            m_dialog->platformSpecificWarning->setText(
                tr("Firewall Builder will import all the rules defined "
                   "in the iptables configuration. Discovered IP networks "
                   "and IP addresses used in the iptables rules will "
                   "automatically have objects created in the object tree. "
                   "Each user defined chain will be created as its own Policy "
                   "object in Firewall Builder."
                   ""
                   "The import process will also attempt to detect interface "
                   "names and IP addresses based on -i and -o parameters in "
                   "the configuration, but you may have to update the firewall "
                   "object with additional interface information like IP addresses."
                ));
            platformOk = true;
        }

        if (detectedPlatform == "iptables" && iptables_c)
        {
            m_dialog->platform->setText(tr("iptables"));
            m_dialog->platformSpecificWarning->setText(
                tr("This appears to be iptables configuration saved using "
                   "command \"iptables-save -c\""
                   "and it includes packet counters. Please save configuration "
                   "using command \"iptables-save\" without option \"-c\" and "
                   "try to import it again."));
            platformOk = false;
        }

        if (detectedPlatform == "pf")
        {
            m_dialog->platform->setText(tr("pf"));
            m_dialog->platformSpecificWarning->setText(
                tr("Import of PF rules is not supported"));
            platformOk = false;
        }

        dynamic_cast<ImportFirewallConfigurationWizard*>(wizard())->
            setPlatform(detectedPlatform);

    }

    emit completeChanged();
}

