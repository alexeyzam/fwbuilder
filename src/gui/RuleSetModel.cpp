/*

                          Firewall Builder

                 Copyright (C) 2009 NetCitadel, LLC

  Author:  Illiya Yalovoy <yalovoy@gmail.com>

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

#include "platforms.h"

#include <string>

#include <QtDebug>
#include <QHash>
#include <QRegExp>
#include <QMessageBox>
#include <QTime>
#include <QtAlgorithms>

#include "fwbuilder/FWObjectDatabase.h"
#include "fwbuilder/Firewall.h"
#include "fwbuilder/Cluster.h"
#include "fwbuilder/Resources.h"
#include "fwbuilder/Policy.h"
#include "fwbuilder/NAT.h"
#include "fwbuilder/Routing.h"
#include "fwbuilder/RuleElement.h"
#include "fwbuilder/Interface.h"

#include "RuleSetModel.h"
#include "FWObjectPropertiesFactory.h"

using namespace libfwbuilder;
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// RuleSetModelIterator
//////////////////////////////////////////////////////////////////////////////////////////////////////////

RuleSetModelIterator::RuleSetModelIterator()
{
    row = 0;
    model = 0;
}

bool RuleSetModelIterator::isValid()
{
    return model != 0 && row>=0 &&  model->rowCount(parent) > row;
}

bool RuleSetModelIterator::hasNext()
{
    if (model->rowCount(parent) - 1 > row) return true;
    return (parent.isValid()) ? (model->rowCount() - 1 > parent.row()) : false;
}

bool RuleSetModelIterator::hasPrev()
{
    if (row > 0) return true;
    return (parent.isValid()) ? (parent.row() > 0) : false;
}

RuleSetModelIterator& RuleSetModelIterator::operator= (const RuleSetModelIterator& it)
{
    model = it.model;
    parent = it.parent;
    row = it.row;

    return *this;
}

RuleSetModelIterator& RuleSetModelIterator::operator++ ()
{
    QModelIndex index = this->index();
    if (model->hasChildren(index))
    {
        parent = index;
        row = 0;
    } else
    {
        row++;
        if (row >= model->rowCount(parent))
        {
            if (parent.isValid())
            {
                row = parent.row() + 1;
                parent = parent.parent();
            }
        }
    }

    return *this;
}
RuleSetModelIterator& RuleSetModelIterator::operator-- ()
{
    row--;
    if (row < 0)
    {
        if (parent.isValid())
        {
            row = parent.row();
            parent = parent.parent();
        }
    } else
    {
        QModelIndex index = this->index();
        if (model->hasChildren(index))
        {
            parent = index;
            row = model->rowCount(parent) - 1;
        }
    }

    return *this;
}

bool RuleSetModelIterator::operator== ( RuleSetModelIterator& it)
{
    return (parent == it.parent) && (row == it.row);
}

bool RuleSetModelIterator::operator!= ( RuleSetModelIterator& it )
{
    return !this->operator==(it);
}

QModelIndex RuleSetModelIterator::index()
{
    return model->index(row, 0,parent);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// RuleSetModel
//////////////////////////////////////////////////////////////////////////////////////////////////////////

RuleSetModel::RuleSetModel(RuleSet *ruleset, QObject *parent) : QAbstractItemModel(parent)
{
    root = 0;
    this->ruleset = ruleset;
    initModel();
}

void RuleSetModel::initModel()
{
    //if (fwbdebug) qDebug() << "RuleSetModel::initModel";
    if (root) delete root;

    root = new RuleNode(RuleNode::Root,"root");

    int row = 1;
    QHash<QString,RuleNode*> groups;
    RuleNode* node;
    RuleNode* group;

    QTime t; t.start();
    for (FWObject::iterator i=ruleset->begin(); i!=ruleset->end(); i++, row++)
    {

        Rule *r = Rule::cast( *i );
        if (r == NULL) continue;  // skip RuleSetOptions

//        rulesByPosition[r->getPosition()] = r;

        node = new RuleNode(RuleNode::Rule, QString());
        node->rule = r;

        if (r->getRuleGroupName().empty())
        {
            root->add(node);
        }
        else
        {
            //Add rule to group
            QString groupName = QString::fromUtf8(r->getRuleGroupName().c_str());
            if (!groups.contains(groupName))
            {
                group = new RuleNode(RuleNode::Group, groupName);
                groups.insert(groupName, group);
                root->add(group);
            }
            else
            {
                group = groups.value(groupName);
            }

            group->add(node);

        }

    }
    //if (fwbdebug) qDebug("Model init: %d ms", t.elapsed());
}

int RuleSetModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;
    RuleNode *parentNode = nodeFromIndex(parent);
    if (!parentNode)
        return 0;
    return parentNode->children.count();
}

int RuleSetModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED (parent)
    return header.size()+1;
}

QVariant RuleSetModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
        case Qt::DisplayRole: return getDataForDisplayRole(index);
        case Qt::UserRole: return getColumnDesc(index);
        case Qt::DecorationRole: return getDecoration(index);
        default: return QVariant();
    }
}

QVariant RuleSetModel::getDecoration(const QModelIndex &index) const
{
    if (!index.isValid()) return QVariant();
    if (index.column() != 0) return QVariant();

    RuleNode *node = nodeFromIndex(index);
    if (!node || node->type != RuleNode::Rule)
        return QVariant();

    if (!node->rule->isDisabled()) return QVariant();

    QVariant res;
    QString icn_file = ":/Icons/neg";

    QPixmap pm;
    LoadPixmap(":/Icons/neg", pm);
    res.setValue( QIcon(pm) );
    return res;
}

QVariant RuleSetModel::getColumnDesc(const QModelIndex &index) const
{
    //if (fwbdebug) qDebug() << "RuleSetModel::getColumnDesc "<< index.column();
    QVariant res;
    if (index.column()>0 && index.column()<=header.size())
    {
        res.setValue(header.at(index.column()-1));
    }
    return res;
}

QVariant RuleSetModel::getDataForDisplayRole(const QModelIndex &index) const {
    //if (fwbdebug) qDebug() << "RuleSetModel::getDataForDisplayRole";
    RuleNode *node = nodeFromIndex(index);
    if (!node)
        return QVariant();

    if (node->type == RuleNode::Group) {
        return getGroupDataForDisplayRole(index,node);
    } else if (node->type == RuleNode::Rule) {
        return getRuleDataForDisplayRole(index,node);
    }

    return QVariant();
}

QVariant RuleSetModel::getGroupDataForDisplayRole(const QModelIndex &index, RuleNode* node) const {
    //if (fwbdebug) qDebug() << "RuleSetModel::getGroupDataForDisplayRole";

    int first = node->children.first()->rule->getPosition();
    int last = node->children.last()->rule->getPosition();

    return (index.column() == 0)?
        QString("%1 (%2 - %3)")
        .arg(node->name)
        .arg(first)
        .arg(last)
        :QVariant();
}

QVariant RuleSetModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //if (fwbdebug) qDebug() << "RuleSetModel::headerData";  // too chatty
    if (orientation == Qt::Vertical)
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();
    if (section>0 && section <= header.size())
        return header[section-1].name;

    return QVariant();
}

Rule * RuleSetModel::findRuleForPosition(int position) const
{
    for (FWObject::iterator i=ruleset->begin(); i!=ruleset->end(); i++)
    {
        Rule *r = Rule::cast( *i );
        if (r->getPosition() == position)
        {
            return r;
        }
    }
    return 0;
}

Rule * RuleSetModel::getRule(QModelIndex index) const
{
    if (!index.isValid()) return 0;
    RuleNode* node = nodeFromIndex(index);
    if (RuleNode::Rule != node->type) return 0;
    return node->rule;
}

QModelIndex RuleSetModel::indexForPosition(int position) const
{
    Rule * res = findRuleForPosition(position);
    return (res == 0)?QModelIndex():index(res, 0);
}

QModelIndex RuleSetModel::index(int row, int column, const QModelIndex &parent) const
{
    // if (fwbdebug)
    //     qDebug() << "RuleSetModel::index(int row, int column, const QModelIndex &parent)"
    //              << "row=" << row
    //              << "column=" << column;

    if (row < 0 || column < 0)
        return QModelIndex();

    RuleNode *parentNode = nodeFromIndex(parent);
    RuleNode *childNode = parentNode->children.value(row);
    if (!childNode)
        return QModelIndex();
    return createIndex(row, column, childNode);

}

QModelIndex RuleSetModel::index(QString groupName) const
{
    if (!groupName.isEmpty())
    {
        int row = 0;
        foreach(RuleNode *node, root->children)
        {
            if (node->type == RuleNode::Group && node->name == groupName)
            {
                return createIndex(row, 0, node);
            }
            row++;
        }
    }
    return QModelIndex();
}

QModelIndex RuleSetModel::index(int row, int column, QString groupName) const
{
    // if (fwbdebug)
    //     qDebug() << " RuleSetModel::index(int row, int column, QString groupName)";
    QModelIndex parent = index(groupName);
    return (parent.isValid()) ? index(row, column, parent) : QModelIndex();
}

QModelIndex RuleSetModel::index(libfwbuilder::Rule *rule, libfwbuilder::RuleElement *re) const
{
    // if (fwbdebug)
    //     qDebug() << "RuleSetModel::index(libfwbuilder::Rule *rule, int col)";
    int col = columnForRuleElementType(re->getTypeName().c_str());
    return index(rule, col);
}

QModelIndex RuleSetModel::index(libfwbuilder::Rule *rule, int col) const
{
    // if (fwbdebug)
    //     qDebug() << "RuleSetModel::index(libfwbuilder::Rule *rule, int col) " << col;
    if (col < 0 || rule == 0) return QModelIndex();
    QModelIndex parent;
    QString groupName = QString::fromUtf8(rule->getRuleGroupName().c_str());
    if (!groupName.isEmpty())
    {
        QList<RuleNode *> topLevel = root->children;
        int row = 0;
        foreach (RuleNode * node, topLevel)
        {
            if (node->type == RuleNode::Group && node->name == groupName)
            {
                parent = createIndex(row, 0, node);
                break;
            }
            row++;
        }
    }
    RuleNode *parentNode = nodeFromIndex(parent);
    int row = 0;
    RuleNode* child = NULL;
    foreach(RuleNode *node, parentNode->children)
    {
        if (node->type == RuleNode::Rule && node->rule == rule)
        {
            child = node;
            break;
        }
        row++;
    }
    if (child == NULL) return QModelIndex();
    return createIndex(row, col, child);
}

int RuleSetModel::columnForRuleElementType(QString typeName) const
{
    // if (fwbdebug)
    //     qDebug() << "RuleSetModel::columnForRuleElementType(QString typeName)";
    int col = 1;
    foreach (ColDesc cd, header)
    {
        if (cd.origin == typeName)
            break;
        col++;
    }
    return col;
}

int RuleSetModel::columnByType(ColDesc::ColumnType type)
{
    // if (fwbdebug)
    //     qDebug() << "RuleSetModel::columnByType(ColDesc::ColumnType type)";
    int col = 1;
    foreach (ColDesc cd, header)
    {
        if (cd.type == type)
            break;
        col++;
    }
    return col;
}

RuleNode *RuleSetModel::nodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        return static_cast<RuleNode *>(index.internalPointer());
    } else {
        return root;
    }
}

QModelIndex RuleSetModel::parent(const QModelIndex &child) const
{
    RuleNode *node = nodeFromIndex(child);
    if (!node)
        return QModelIndex();
    RuleNode *parentNode = node->parent;
    if (!parentNode)
        return QModelIndex();
    RuleNode *grandparentNode = parentNode->parent;
    if (!grandparentNode)
        return QModelIndex();

    int row = grandparentNode->children.indexOf(parentNode);
    return createIndex(row, 0, parentNode);
}

RuleElement * RuleSetModel::getRuleElementByRole(Rule* r, string roleName) const
{
    return RuleElement::cast( r->getFirstByType(roleName) );
}

bool RuleSetModel::isEmpty()
{
    return root->children.size() == 0;
}

Firewall* RuleSetModel::getFirewall() const
{
    FWObject *f=ruleset;
    while (f!=NULL && (!Firewall::isA(f) && !Cluster::isA(f))) f=f->getParent();
    // f can be NULL if user is looking at deleted ruleset which is a child
    // of the library DeletedObjects
    return Firewall::cast(f);
}

void RuleSetModel::insertRuleToModel(Rule *rule, QModelIndex &index, bool isAfter)
{

    QModelIndex parent = index.parent();

    RuleNode *newNode = new RuleNode(RuleNode::Rule, QString());
    newNode->rule = rule;
    if (index.isValid())
    {
        RuleNode *node = nodeFromIndex(index);
        int idx =  node->parent->children.indexOf(node);
        if (isAfter) idx++;
        emit beginInsertRows(parent, idx, idx);
        node->parent->children.insert(idx, newNode);
        newNode->parent = node->parent;
        emit endInsertRows();
    }
    else
    {
        emit beginInsertRows(parent, 0, 0);
        root->children.prepend(newNode);
        newNode->parent = root;
        emit endInsertRows();
    }
}

Rule* RuleSetModel::insertNewRule()
{
    Rule *newrule = getRuleSet()->insertRuleAtTop();
    initRule(newrule);
    QModelIndex index;
    insertRuleToModel(newrule, index);
    return newrule;
}

Rule* RuleSetModel::insertNewRule(QModelIndex &index, bool isAfter)
{
    if (!index.isValid()) return insertNewRule();
    RuleNode *node = nodeFromIndex(index);
    int pos = node->rule->getPosition();
    Rule *newrule = isAfter?ruleset->appendRuleAfter(pos):ruleset->insertRuleBefore(pos);
    initRule(newrule);
    string groupName = node->rule->getRuleGroupName();
    newrule->setRuleGroupName(groupName);
    insertRuleToModel(newrule, index, isAfter);
    return newrule;
}

Rule* RuleSetModel::insertRule(Rule *rule, QModelIndex &index, bool isAfter)
{
    Rule *newrule = 0;
    if (index.isValid())
    {
        RuleNode *node = nodeFromIndex(index);
        int pos = node->rule->getPosition();
        newrule = isAfter?ruleset->appendRuleAfter(pos):ruleset->insertRuleBefore(pos);
        initRule(newrule, rule);
        string groupName = node->rule->getRuleGroupName();
        newrule->setRuleGroupName(groupName);
        insertRuleToModel(newrule, index, isAfter);
    }
    else
    {
        newrule = getRuleSet()->insertRuleAtTop();
        initRule(newrule, rule);
        QModelIndex index;
        insertRuleToModel(newrule, index);
    }
    return newrule;
}

void RuleSetModel::restoreRule(Rule* rule)
{

}

void RuleSetModel::restoreRules(QList<Rule*> rules, bool topLevel)
{
//    qDebug() << "RuleSetModel::restoreRules(QList<Rule*> rules)";

    int pos = rules.first()->getPosition()-1;
    int last = 0;
    Rule* pivotRule = 0;
    QModelIndex pivotIndex;

    //The very top rule should be inserted BEFORE others
    if (pos < 0)
    {
        Rule* rule = rules.first();
        pivotRule = ruleset->getRuleByNum(0);
        ruleset->insert_before(pivotRule, rule);
        pivotIndex = index(pivotRule, 0);

        if (topLevel && pivotIndex.parent().isValid())
        {
            pivotIndex = pivotIndex.parent();
        }
        insertRuleToModel(rule, pivotIndex, false);

        pivotRule = rule;
        last++;
    } else
    {
        pivotRule = ruleset->getRuleByNum(pos);
    }

    pivotIndex = index(pivotRule, 0);

    // We need a toplevel index
    if (topLevel && pivotIndex.parent().isValid())
    {
        pivotIndex = pivotIndex.parent();
    }

    for (int i=rules.size()-1; i>=last; i--)
    {
        Rule* rule = rules.at(i);
        ruleset->insert_after(pivotRule, rule);

        insertRuleToModel(rule, pivotIndex, true);

    }
    ruleset->renumberRules();
}

void RuleSetModel::removeRow(int row,const QModelIndex &parent)
{
    removeRows(row,1,parent);
}

bool RuleSetModel::removeRows(int row, int count, const QModelIndex &parent)
{
    //if (fwbdebug) qDebug() << "RuleSetModel::removeRows " << row << " , " << count ;

    if (count < 1 || row < 0 || (row + count > rowCount(parent)))
        return false;

    RuleNode *parentNode = nodeFromIndex(parent);

    int lastRow = row + count - 1;

    beginRemoveRows(parent,row,lastRow);

    for (int i = 0; i<count; i++)
    {

        RuleNode *oldNode = parentNode->children.at(row);

        if (oldNode->type == RuleNode::Group || ruleset->deleteRule(oldNode->rule) )
        {
            parentNode->children.removeAt(row);
            delete oldNode;
        } else {
            //TODO: May be we need some othe action in this case
             qWarning() << "Failed to remove rule";
             break;
        }
    }

    endRemoveRows();
    return true;
}

void RuleSetModel::moveRuleUp(const QModelIndex &group, int first, int last)
{
    RuleNode *groupNode = nodeFromIndex(group);

    if (groupNode->isRoot())
    {
        if (first == 0) return;
        if (root->children.at(first - 1)->type == RuleNode::Group)
        {
            addToGroupAbove(first, last);
            return;
        }
    }
    else
    {
        if (first == 0)
        {
            removeFromGroup(group, first, last);
            return;
        }
    }

    int pos = first - 1;

    QList<RuleNode*> list;
    removeToList(list, group, first, last);

    for(int i = 0; i< list.size(); i++)
    {
        ruleset->moveRuleUp(list.at(i)->rule->getPosition());
    }

    insertFromList(list, group, pos);
}

void RuleSetModel::moveRuleDown(const QModelIndex &group, int first, int last)
{
    RuleNode *groupNode = nodeFromIndex(group);

    int childrens = groupNode->children.size();

    if (groupNode->isRoot())
    {
        if (last == childrens - 1) return;
        if (root->children.at(last + 1)->type == RuleNode::Group)
        {
            addToGroupBelow(first, last);
            return;
        }
    }
    else
    {
        if (last == childrens - 1)
        {
            removeFromGroup(group, first, last);
            return;
        }
    }

    int pos = first + 1;

    QList<RuleNode*> list;
    removeToList(list, group, first, last);

    for(int i = list.size() - 1; i>=0 ; i--)
    {
        ruleset->moveRuleDown(list.at(i)->rule->getPosition());
    }

    insertFromList(list, group, pos);
}

void RuleSetModel::removeToList(QList<RuleNode*> &list, const QModelIndex &group, int first, int last)
{
    emit beginRemoveRows(group, first, last);

    int count = last - first + 1;

    RuleNode *parent = nodeFromIndex(group);

    for (int i=0; i<count; i++)
    {
        list << parent->children.at(first);
        parent->children.removeAt(first);
    }

    emit endRemoveRows();
}

void RuleSetModel::insertFromList(const QList<RuleNode*> &list, const QModelIndex &group, int position)
{
    int first = position;
    int last = position + list.size() - 1;

    emit beginInsertRows(group, first, last);

    RuleNode *parent = nodeFromIndex(group);
    for (int i=list.size()-1; i>=0; i--)
    {
        parent->children.insert(position, list.at(i));
    }

    emit endInsertRows();
}

bool RuleSetModel::isIndexRule(const QModelIndex index)
{
    if (!index.isValid()) return false;
    RuleNode* node = static_cast<RuleNode *>(index.internalPointer());
    if (node == 0) return false;
    return node->type == RuleNode::Rule;
}

void RuleSetModel::changeRuleColor(const QList<QModelIndex> &indexes, const QString &c)
{
    QModelIndex i1 = index(indexes.first().row(), 0, indexes.first().parent());
    QModelIndex i2 = index(indexes.last().row(), header.size() - 1, indexes.last().parent());

    foreach(QModelIndex index, indexes)
    {
        if (!index.isValid()) return;
        RuleNode* node = nodeFromIndex(index);
        if (node->rule==0) return;
        FWOptions *ropt = node->rule->getOptionsObject();
        ropt->setStr("color", c.toLatin1().constData());
    }
    emit dataChanged(i1, i2);
}

void RuleSetModel::changeGroupColor(const QModelIndex index, const QString &c)
{
    if (!index.isValid()) return;
    RuleNode* group = nodeFromIndex(index);
    if (group->type != RuleNode::Group) return;

    foreach (RuleNode* node, group->children)
    {
        if (node->rule==0) continue;
        FWOptions *ropt = node->rule->getOptionsObject();
        ropt->setStr("color", c.toLatin1().constData());
    }
    groupChanged(index);
}

void RuleSetModel::renameGroup(QModelIndex group, const QString &newName)
{
    QString newGroupName = findUniqueNameForGroup(newName);
    RuleNode* groupNode = nodeFromIndex(group);

    //Set new group name for all children of this node.

    foreach (RuleNode* node, groupNode->children)
    {
        node->rule->setRuleGroupName(newGroupName.toUtf8().data());
    }
    groupNode->name = newGroupName;

    rowChanged(group);
}

void RuleSetModel::rowChanged(const QModelIndex &index)
{
    nodeFromIndex(index)->resetSizes();
    emit dataChanged(createIndex(index.row(), 0, index.internalPointer()), createIndex(index.row(), header.size()-1,index.internalPointer()));
}

void RuleSetModel::groupChanged(const QModelIndex &group)
{
    RuleNode* groupNode = nodeFromIndex(group);
    QModelIndex i1 = index(0,0,group);
    QModelIndex i2 = index(groupNode->children.size() - 1, header.size()-1, group);
    emit dataChanged(i1, i2);
}

QString RuleSetModel::findUniqueNameForGroup(const QString &groupName)
{
    int count = 0;

    bool exactNameExists = false;

    QRegExp rx("^(.*)-(\\d+)$");

    foreach (RuleNode *node, root->children)
    {
        if (node->type != RuleNode::Group) continue;

        QString name = node->name;

        exactNameExists = exactNameExists || (name == groupName);

        if (rx.exactMatch(name))
        {
            QString nameSection = rx.capturedTexts().at(1);
            QString countSection = rx.capturedTexts().at(2);

            int curCnt = countSection.toInt();

            if (nameSection == groupName && curCnt>count)
                count = curCnt;
        }

    }

    QString uniqueGroupName = (exactNameExists)? groupName + "-" + QString::number(++count):groupName;

    //if (fwbdebug) qDebug() << "uniqueGroupName" << uniqueGroupName ;

    return uniqueGroupName;
}

QModelIndex RuleSetModel::createNewGroup(QString groupName, int first, int last)
{
    //if (fwbdebug) qDebug() << "RuleSetModel::createNewGroup" << groupName << first << last;
    QString uniqueGroupName = findUniqueNameForGroup(groupName);

    RuleNode *group = new RuleNode(RuleNode::Group, uniqueGroupName);

     // remove selected rules

    emit beginRemoveRows(QModelIndex(), first, last);
    int count = last - first + 1;
    for(int i=0; i<count; i++)
    {
        RuleNode *node = root->children.at(first);
        group->add(node);
        root->children.removeAt(first);
        node->rule->setRuleGroupName(uniqueGroupName.toUtf8().data());
    }
    emit endRemoveRows();

    // Add new group after the selected rules

    int groupPos = first;
    emit beginInsertRows(QModelIndex(), groupPos, groupPos);
    root->insert(groupPos, group);
    emit endInsertRows();

    return index(groupPos, 0, QModelIndex());

}

void RuleSetModel::removeFromGroup(QModelIndex group, int first, int last)
{
    if (!group.isValid()) return;
    RuleNode *groupNode = nodeFromIndex(group);
    if (groupNode->type != RuleNode::Group) return;
    //if (fwbdebug) qDebug() << "RuleSetModel::removeFromGroup " << groupNode->name << first << "-" << last;

    /*
        if items touch bottom of the group or we are going to move all items from the group
        then we will insert them after the group node one level up, Else we will insert them before\
        the group node.
    */

    int count = last-first+1;
    bool moveAllItems = count == groupNode->children.size();
    bool insertBefore = first == 0;
    int insertPosition = (insertBefore || moveAllItems)?group.row():(group.row()+1);

    // Remove nodes from the tree

    emit beginRemoveRows(group, first, last);

    QList<RuleNode*> moving;
    for(int i = first; i<= last; i++)
    {
        RuleNode *node = groupNode->children.at(first);
        node->rule->setRuleGroupName("");
        moving << node;;
        groupNode->children.removeAt(first);
    }

    emit endRemoveRows();

    QModelIndex rootIndex = group.parent();

    // if all Items were moved from the group then group should be removed as well

    if (moveAllItems)
    {
        emit  beginRemoveRows(rootIndex, group.row(), group.row());
        root->children.removeAt(group.row());
        delete groupNode;
        emit endRemoveRows();
    }

    emit beginInsertRows(rootIndex, insertPosition, insertPosition + count -1);

    // Insert rows to calculated position.

    int pos = insertPosition;

    for(int i=0; i<count; i++)
    {
        root->insert(pos++,moving.at(i));
    }
    emit endInsertRows();
}

QString RuleSetModel::addToGroupAbove(int first, int last)
{
    RuleNode *targetGroup = root->children.at(first - 1);
    moveToGroup(targetGroup, first, last);
    return targetGroup->name;
}

QString RuleSetModel::addToGroupBelow(int first, int last)
{
    RuleNode *targetGroup = root->children.at(last + 1);
    moveToGroup(targetGroup, first, last, false);
    return targetGroup->name;
}

void RuleSetModel::moveToGroup(RuleNode *targetGroup, int first, int last, bool append)
{
    //if (fwbdebug) qDebug() << "RuleSetModel::moveToGroup " << targetGroup->name << first << last << append;
    // Remove nodes from the tree
    QList<RuleNode*> rules;
    emit beginRemoveRows(QModelIndex(), first, last);
    int count = last - first + 1;
    for(int i=0; i<count; i++)
    {
        RuleNode *node = root->children.at(first);
        rules << node;
        root->children.removeAt(first);
        node->rule->setRuleGroupName(targetGroup->name.toStdString());
    }
    emit endRemoveRows();

    // Add rules to the group

    int row = (append)?first - 1:first;
    QModelIndex targetGroupIndex = createIndex(row, 0, targetGroup);;
    emit beginInsertRows(targetGroupIndex,
                         (append)?targetGroup->children.size():0,
                         (append)?(targetGroup->children.size()+count-1):(count-1)
                         );

    for(int i=0; i<count; i++)
    {
        if (append)
            targetGroup->add(rules.at(i));
        else
            targetGroup->prepend(rules.at(count - i - 1));
    }
    emit endInsertRows();
}

void RuleSetModel::setEnabled(const QModelIndex &index, bool flag)
{
    if (!index.isValid()) return;
    RuleNode *node = nodeFromIndex(index);
    if (node->type != RuleNode::Rule) return;
    //if (fwbdebug) qDebug() << "RuleSetModel::setEnabled " << index.row() << "->" << flag;

    if (flag)
        node->rule->enable();
    else
        node->rule->disable();

    rowChanged(index);
}

void RuleSetModel::deleteObject(QModelIndex &index, FWObject* obj)
{
    RuleElement *re = (RuleElement *)index.data(Qt::DisplayRole).value<void *>();

    if (re==NULL || re->isAny()) return;
//    int id = obj->getId();

    // if (fwbdebug)
    // {
    //     qDebug("RuleSetView::deleteObject row=%d col=%d id=%s",
    //            index.row(), index.column(), FWObjectDatabase::getStringId(id).c_str());
    //     qDebug("obj = %p",re->getRoot()->findInIndex(id));
    //     int rc = obj->ref()-1;  obj->unref();
    //     qDebug("obj->ref_counter=%d",rc);
    // }

    re->removeRef(obj);

    if (re->isAny()) re->setNeg(false);
    rowChanged(index);

    // if (fwbdebug)
    // {
    //     qDebug("RuleSetView::deleteObject re->size()=%d", int(re->size()));
    //     qDebug("obj = %p",re->getRoot()->findInIndex(id));
    //     int rc = obj->ref()-1;  obj->unref();
    //     qDebug("obj->ref_counter=%d",rc);
    // }
}

bool RuleSetModel::insertObject(QModelIndex &index, FWObject *obj)
{
    // if (fwbdebug) qDebug("RuleSetModel::insertObject  -- insert object %s",
    //            obj->getName().c_str());


    ColDesc colDesc = index.data(Qt::UserRole).value<ColDesc>();
    if (colDesc.type != ColDesc::Object && colDesc.type != ColDesc::Time) return false;

    RuleElement *re = (RuleElement *)index.data(Qt::DisplayRole).value<void *>();
    assert (re!=NULL);

    if (! re->validateChild(obj) )
    {
        if (RuleElementRItf::cast(re))
        {
            QMessageBox::information( NULL , "Firewall Builder",
                "A single interface belonging to this firewall is expected in this field.",
                QString::null,QString::null);
        }
        else if (RuleElementRGtw::cast(re))
        {
            QMessageBox::information( NULL , "Firewall Builder",
                "A single ip adress is expected here. You may also insert a host or a network adapter leading to a single ip adress.",
                QString::null,QString::null);
        }
        return false;
    }

    if (re->getAnyElementId()==obj->getId()) return false;

    if ( !re->isAny())
    {
        /* avoid duplicates */
        int cp_id = obj->getId();
        list<FWObject*>::iterator j;
        for(j=re->begin(); j!=re->end(); ++j)
        {
            FWObject *o=*j;
            if(cp_id==o->getId()) return false;

            FWReference *ref;
            if( (ref=FWReference::cast(o))!=NULL &&
                 cp_id==ref->getPointerId()) return false;
        }
    }

    re->addRef(obj);

    rowChanged(index);

    return true;
}

void RuleSetModel::getGroups(QList<QModelIndex> &list)
{
    list.clear();
    int row = 0;
    foreach(RuleNode *node, root->children)
    {
        if (node->type == RuleNode::Group)
        {
            list.append(createIndex(row, 0, node));
        }
        row++;
    }
}

RuleSetModelIterator RuleSetModel::begin()
{
    RuleSetModelIterator it;
    if (root->children.isEmpty()) return it;
    it.model = this;
    it.row = 0;
    return it;
}
RuleSetModelIterator RuleSetModel::end()
{
    RuleSetModelIterator it;
    if (root->children.isEmpty()) return it;
    it.model = this;
    RuleNode *node = root->children.last();
    if (node->type == RuleNode::Group)
    {
        QModelIndex parent = createIndex(root->children.size() - 1, 0, node);
        it.parent = parent;
        it.row = node->children.size();
    } else
    {
        it.row = root->children.size();
    }

    return it;
}

bool RuleSetModel::isGroup(const QModelIndex &index) const
{
    RuleNode* node = nodeFromIndex(index);

    return node != NULL && node->type == RuleNode::Group;
}

void RuleSetModel::resetAllSizes()
{
    root->resetAllSizes();
}

QString RuleSetModel::getPositionAsString(RuleNode *node) const
{
    return QString::number(node->rule->getPosition());
}

ActionDesc RuleSetModel::getRuleActionDesc(Rule* r) const
{
    ActionDesc res;
    res.name = getRuleAction(r);
    res.displayName = getActionNameForPlatform(getFirewall(), r);
    res.tooltip = FWObjectPropertiesFactory::getRuleActionPropertiesRich(r);

    QString par = FWObjectPropertiesFactory::getRuleActionProperties(r);
    if (!par.isEmpty()) {
        if (par.length() > 20)
            par = par.left(17) + "...";
        res.displayName += ":"+par;
    }

    return res;
}

int RuleSetModel::getRulePosition(QModelIndex index)
{
    Rule* rule = 0;
    if (index.isValid())
    {
        rule = nodeFromIndex(index)->rule;
    }
    return (rule == 0)?0:rule->getPosition();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// PolicyModel
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void PolicyModel::configure()
{
    supports_logging      = false;
    supports_rule_options = false;
    supports_time         = false;

    if (getFirewall())
    {
        try {
            supports_logging = Resources::getTargetCapabilityBool(
                    getFirewall()->getStr("platform"), "logging_in_policy");
            supports_rule_options = Resources::getTargetCapabilityBool(
                    getFirewall()->getStr("platform"), "options_in_policy");
            supports_time = Resources::getTargetCapabilityBool(
                    getFirewall()->getStr("platform"), "supports_time");
        } catch(FWException &ex)    {    }
    }

    header  << ColDesc(RuleElementSrc::TYPENAME, ColDesc::Object)   // 1
            << ColDesc(RuleElementDst::TYPENAME, ColDesc::Object)   // 2
            << ColDesc(RuleElementSrv::TYPENAME, ColDesc::Object)   // 3
            << ColDesc(RuleElementItf::TYPENAME, ColDesc::Object)   // 4
            << ColDesc("Direction", ColDesc::Direction)             // 5
            << ColDesc("Action", ColDesc::Action);                  // 6
    if (supports_time)
        header << ColDesc(RuleElementInterval::TYPENAME, ColDesc::Time);  // 7

    if (supports_logging && supports_rule_options)
        header << ColDesc("Options", ColDesc::Options);

    header << ColDesc("Comment", ColDesc::Comment);
}

QVariant PolicyModel::getRuleDataForDisplayRole(const QModelIndex &index, RuleNode* node) const
{
    QVariant res;

    QTime t;

    if (index.column() == 0)
    {
        res.setValue(getPositionAsString(node));
    } else if (index.column() <= header.size())
    {
        int idx = index.column()-1;
        switch (header[idx].type)
        {
            case ColDesc::Action :
                res.setValue<ActionDesc>(getRuleActionDesc(node->rule));
                break;

            case ColDesc::Direction :
                res.setValue<QString>(getRuleDirection(node->rule));
                break;

            case ColDesc::Options :
                res.setValue<QStringList>(getRuleOptions(node->rule));
                break;

            case ColDesc::Comment :
                res.setValue<QString>(QString::fromUtf8(node->rule->getComment().c_str()));
                break;

            default :
                res.setValue<void *>(getRuleElementByRole(node->rule, header[idx].origin.toStdString()));
        }
    }
    return res;
}

QString PolicyModel::getRuleDirection(Rule* r) const
{
    PolicyRule *policyRule = PolicyRule::cast( r );
    QString dir = policyRule->getDirectionAsString().c_str();
    if (dir.isEmpty() || dir == "Undefined") dir = "Both";
    return dir;
}

QStringList PolicyModel::getRuleOptions(Rule* r) const
{
    QStringList res;
    PolicyRule  *policyRule  = PolicyRule::cast( r );
    if (policyRule->getLogging()) res << "Log";
    if (!isDefaultPolicyRuleOptions(r->getOptionsObject())) res << "Options";

    return res;
}

void PolicyModel::initRule(Rule *new_rule, Rule *old_rule)
{
    //if (fwbdebug) qDebug() << "PolicyModel::initRule";
    PolicyRule *newrule_as_policy_rule = PolicyRule::cast(new_rule);
    if (newrule_as_policy_rule)
    {
        newrule_as_policy_rule->setLogging(supports_logging);
        newrule_as_policy_rule->setAction(PolicyRule::Deny);
        newrule_as_policy_rule->setDirection(PolicyRule::Both);
        FWOptions *ruleopt = newrule_as_policy_rule->getOptionsObject();
        ruleopt->setBool("stateless",
                         getStatelessFlagForAction(newrule_as_policy_rule));
    }
    if (old_rule!=NULL)
    {
        int oldPos = new_rule->getPosition();
        new_rule->duplicate(old_rule);
        new_rule->setPosition(oldPos);
    }
}

bool PolicyModel::checkRuleType(libfwbuilder::Rule *rule)
{
    return rule->getTypeName() == PolicyRule::TYPENAME;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
// NatModel
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatModel::configure()
{
    supports_actions = false;

    if (getFirewall())
    {
        try {
            supports_actions = Resources::getTargetCapabilityBool(
                getFirewall()->getStr("platform"), "actions_in_nat");
        } catch(FWException &ex)    {    }
    }

    header  << ColDesc(RuleElementOSrc::TYPENAME, ColDesc::Object)   // 1
            << ColDesc(RuleElementODst::TYPENAME, ColDesc::Object)   // 2
            << ColDesc(RuleElementOSrv::TYPENAME, ColDesc::Object)   // 3
            << ColDesc(RuleElementTSrc::TYPENAME, ColDesc::Object)   // 4
            << ColDesc(RuleElementTDst::TYPENAME, ColDesc::Object)   // 5
            << ColDesc(RuleElementTSrv::TYPENAME, ColDesc::Object);   // 6

    if (supports_actions)
        header << ColDesc("Action", ColDesc::Action);

    header << ColDesc("Options", ColDesc::Options)                  // 7
           << ColDesc("Comment", ColDesc::Comment);                 // 8
}

QVariant NatModel::getRuleDataForDisplayRole(const QModelIndex &index, RuleNode* node) const
{
    //if (fwbdebug) qDebug() << "NatModel::getRuleDataForDisplayRole";

    QVariant res;

    if (index.column() == 0)
    {
        res.setValue(getPositionAsString(node));
    } else if (index.column() <= header.size())
    {
        int idx = index.column()-1;
        switch (header[idx].type)
        {
            case ColDesc::Action :
                res.setValue<ActionDesc>(getRuleActionDesc(node->rule));
                break;

            case ColDesc::Options :
                res.setValue<QStringList>(getRuleOptions(node->rule));
                break;

            case ColDesc::Comment :
                res.setValue<QString>(QString::fromUtf8(node->rule->getComment().c_str()));
                break;

            default :
                res.setValue<void *>(getRuleElementByRole(node->rule, header[idx].origin.toStdString()));

        }
    }
    return res;
}



QStringList NatModel::getRuleOptions(Rule* r) const
{
    QStringList res;

    if (!isDefaultNATRuleOptions(r->getOptionsObject())) res << "Options";

    return res;
}

void NatModel::initRule(Rule *new_rule, Rule *old_rule)
{
    //if (fwbdebug) qDebug() << "NatModel::initRule";
    NATRule  *natRule = NATRule::cast(new_rule);
    if (natRule)
        natRule->setAction(NATRule::Translate);

    if (old_rule!=NULL)  new_rule->duplicate(old_rule);
}

bool NatModel::checkRuleType(libfwbuilder::Rule *rule)
{
    return rule->getTypeName() == NATRule::TYPENAME;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoutingModel
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoutingModel::configure()
{
    //if (fwbdebug) qDebug() << "RoutingModel::configure";
    supports_routing_itf  = false;

    if (getFirewall())
    {
        try {
            supports_routing_itf =
                Resources::getTargetCapabilityBool(
                        getFirewall()->getStr("platform"), "supports_routing_itf");
        } catch(FWException &ex)    {    }
    }

    header  << ColDesc(RuleElementRDst::TYPENAME, ColDesc::Object)   // 1
            << ColDesc(RuleElementRGtw::TYPENAME, ColDesc::Object);  // 2

    if (supports_routing_itf)
        header << ColDesc(RuleElementRItf::TYPENAME, ColDesc::Object);

    header  << ColDesc("Metric", ColDesc::Metric)
            << ColDesc("Options", ColDesc::Options)
            << ColDesc("Comment", ColDesc::Comment);
}

QVariant RoutingModel::getRuleDataForDisplayRole(const QModelIndex &index, RuleNode* node) const
{
    //if (fwbdebug) qDebug() << "RoutingModel::getRuleDataForDisplayRole";

    QVariant res;

    if (index.column() == 0)
    {
        res.setValue(getPositionAsString(node));
    } else if (index.column() <= header.size())
    {
        int idx = index.column()-1;
        switch (header[idx].type)
        {
            case ColDesc::Metric :
                res.setValue<QString>(QString::fromUtf8(RoutingRule::cast(node->rule)->getMetricAsString().c_str()));
                break;

            case ColDesc::Options :
                res.setValue<QStringList>(getRuleOptions(node->rule));
                break;

            case ColDesc::Comment :
                res.setValue<QString>(QString::fromUtf8(node->rule->getComment().c_str()));
                break;

            default :
                res.setValue<void *>(getRuleElementByRole(node->rule, header[idx].origin.toStdString()));

        }
    }
    return res;
}

QStringList RoutingModel::getRuleOptions(Rule* r) const
{
    QStringList res;

    if (!isDefaultRoutingRuleOptions(r->getOptionsObject())) res << "Options";

    return res;
}

void RoutingModel::initRule(Rule *new_rule, Rule *old_rule)
{
    //if (fwbdebug) qDebug() << "RoutingModel::initRule";
    if (old_rule!=NULL)  new_rule->duplicate(old_rule);
}

bool RoutingModel::checkRuleType(libfwbuilder::Rule *rule)
{
    return rule->getTypeName() == RoutingRule::TYPENAME;
}
