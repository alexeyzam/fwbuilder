/* 

                          Firewall Builder

                 Copyright (C) 2000 NetCitadel, LLC

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

#include <assert.h>
#include <sstream>
#include <iostream>

#include <fwbuilder/libfwbuilder-config.h>

#include <fwbuilder/FWObjectDatabase.h>
#include <fwbuilder/Firewall.h>
#include <fwbuilder/Rule.h>
#include <fwbuilder/RuleElement.h>
#include <fwbuilder/Policy.h>
#include <fwbuilder/FWOptions.h>
#include <fwbuilder/XMLTools.h>
#include <fwbuilder/Policy.h>
#include <fwbuilder/NAT.h>
#include <fwbuilder/Routing.h>
#include <fwbuilder/TagService.h>

using namespace std;
using namespace libfwbuilder;
 
const char *Rule::TYPENAME={"Rule"};

Rule::Rule()
{
    setInt("position",0);
    enable();
    setFallback(false);
    setHidden(false);
    setRuleGroupName("");
}

Rule::Rule(const FWObjectDatabase *root,bool prepopulate) : Group(root,prepopulate)
{
    setInt("position",0);
    enable();
    setFallback(false);
    setHidden(false);
}

FWOptions* Rule::getOptionsObject()  {    return NULL;              }
RuleSet*   Rule::getBranch()         {    return NULL;              }
void       Rule::setPosition(int n)  {    setInt("position",n);     }
int        Rule::getPosition() const {    return getInt("position");}
void       Rule::disable()           {    setBool("disabled",true); }
void       Rule::enable()            {    setBool("disabled",false);}
bool       Rule::isDisabled() const  {    return( getBool("disabled") );}
bool       Rule::isEmpty()           {    return false;             }

void Rule::setBranch(RuleSet*) {};

string Rule::getRuleGroupName() const { return getStr("group"); }

void Rule::setRuleGroupName(const std::string &group_name)
{
    setStr("group", group_name);
}



FWObject& Rule::shallowDuplicate(const FWObject *x,
                                 bool preserve_id) throw(FWException)
{
    const Rule *rx=Rule::constcast(x);
    fallback = rx->fallback;
    hidden = rx->hidden;
    label = rx->label;
    unique_id = rx->unique_id;
    abs_rule_number = rx->abs_rule_number;

    return  FWObject::shallowDuplicate(x,preserve_id);
}


/***************************************************************************/

const char *PolicyRule::TYPENAME={"PolicyRule"};

PolicyRule::PolicyRule()
{
//    setStr("action","Deny");
    setAction(PolicyRule::Deny);

    src_re = NULL;
    dst_re = NULL;
    srv_re = NULL;
    itf_re = NULL;
    when_re = NULL;
}

PolicyRule::PolicyRule(const FWObjectDatabase *root,bool prepopulate) : Rule(root,prepopulate)
{
//    setStr("action","Deny");
    setAction(PolicyRule::Deny);

    src_re = NULL;
    dst_re = NULL;
    srv_re = NULL;
    itf_re = NULL;
    when_re = NULL;

    if (prepopulate)
    {
        FWObject         *re;
        FWObjectDatabase *db=(FWObjectDatabase*)root;
        assert(db);

// <!ELEMENT PolicyRule (Src,Dst,Srv?,Itf?,When?,PolicyRuleOptions?)>
        re = db->createRuleElementSrc();  assert(re!=NULL);
        add(re); src_re = RuleElementSrc::cast(re);

        re = db->createRuleElementDst();  assert(re!=NULL);
        add(re); dst_re = RuleElementDst::cast(re);

        re = db->createRuleElementSrv();  assert(re!=NULL);
        add(re); srv_re = RuleElementSrv::cast(re);

        re = db->createRuleElementItf();  assert(re!=NULL);
        add(re); itf_re = RuleElementItf::cast(re);

        re = db->createRuleElementInterval(); assert(re!=NULL);
        add(re); when_re = RuleElementInterval::cast(re);

        add( db->createPolicyRuleOptions() );
    }
}

FWObject& PolicyRule::shallowDuplicate(const FWObject *x,
                                       bool preserve_id) throw(FWException)
{
    const PolicyRule *rx=PolicyRule::constcast(x);
    setDirection(rx->getDirection());
    setAction(rx->getAction());
    setLogging(rx->getLogging());

    src_re = NULL;
    dst_re = NULL;
    srv_re = NULL;
    itf_re = NULL;
    when_re = NULL;

    return  Rule::shallowDuplicate(x, preserve_id);
}

// <!ELEMENT PolicyRule (Src,Dst,Srv?,Itf?,When?,PolicyRuleOptions?)>
RuleElementSrc*  PolicyRule::getSrc()
{
    if (src_re) return src_re;
    FWObject::iterator i1 = begin();
    src_re = RuleElementSrc::cast(*i1);
    return src_re;
}

RuleElementDst*  PolicyRule::getDst()
{
    if (dst_re) return dst_re;
    FWObject::iterator i1 = begin();
    i1++;
    dst_re = RuleElementDst::cast(*i1);
    return dst_re;
}

RuleElementSrv*  PolicyRule::getSrv()
{
    if (srv_re) return srv_re;
    FWObject::iterator i1 = begin();
    i1++;
    i1++;
    srv_re = RuleElementSrv::cast(*i1);
    return srv_re;
}

RuleElementItf*  PolicyRule::getItf()
{
    if (itf_re) return itf_re;
    FWObject::iterator i1 = begin();
    i1++;
    i1++;
    i1++;
    itf_re = RuleElementItf::cast(*i1);
    return itf_re;
}

RuleElementInterval* PolicyRule::getWhen()
{
    if (when_re) return when_re;
    FWObject::iterator i1 = begin();
    i1++;
    i1++;
    i1++;
    i1++;
    when_re = RuleElementInterval::cast(*i1);
    return when_re;
}

bool PolicyRule::isEmpty()
{
  return (getSrc()->isAny() && 
          getDst()->isAny() && 
          getSrv()->isAny() && 
          getItf()->isAny());
}

string PolicyRule::getActionAsString() const
{
    switch (action) {
    case Accept:     return "Accept";
    case Deny:       return "Deny";
    case Reject:     return "Reject";
    case Scrub:      return "Scrub";
    case Return:     return "Return";
    case Skip:       return "Skip";
    case Continue:   return "Continue";
    case Accounting: return "Accounting";
    case Modify:     return "Modify";
    case Tag:        return "Tag";
    case Pipe:       return "Pipe";
    case Classify:   return "Classify";
    case Custom:     return "Custom";
    case Branch:     return "Branch";
    case Route:      return "Route";
    default:         return "Unknown";
    }
    return "Deny";
}

void PolicyRule::setAction(const string& act)
{
    if (act=="Accept")     { setAction(Accept); return; }
    if (act=="Deny")       { setAction(Deny); return; }
    if (act=="Reject")     { setAction(Reject); return; }
    if (act=="Scrub")      { setAction(Scrub); return; }
    if (act=="Return")     { setAction(Return); return; }
    if (act=="Skip")       { setAction(Skip); return; }
    if (act=="Continue")   { setAction(Continue); return; }
    if (act=="Accounting") { setAction(Accounting); return; }
    if (act=="Modify")     { setAction(Modify); return; }
    if (act=="Tag")        { setAction(Tag); return; }
    if (act=="Pipe")       { setAction(Pipe); return; }
    if (act=="Classify")   { setAction(Classify); return; }
    if (act=="Custom")     { setAction(Custom); return; }
    if (act=="Branch")     { setAction(Branch); return; }
    if (act=="Route")      { setAction(Route); return; }
    setAction(Deny);
}

string PolicyRule::getDirectionAsString() const
{
    switch (direction)
    {
    case Inbound:   return "Inbound";
    case Outbound:  return "Outbound";
    case Both:      return "Both";
    default:        return "Both";
    }
}

void PolicyRule::setDirection(const string& dir)
{
    if (dir=="Inbound")   { setDirection(Inbound); return; }
    if (dir=="Outbound")  { setDirection(Outbound); return; }
    setDirection(Both);
}

bool   PolicyRule::getLogging() const    { return getBool("log"); }
void   PolicyRule::setLogging(bool flag) { setBool("log",flag);   }


void PolicyRule::fromXML(xmlNodePtr root) throw(FWException)
{
    const char* n;

    FWObject::fromXML(root);

    n=FROMXMLCAST(xmlGetProp(root,TOXMLCAST("position")));
    if(n)
    {
        setInt("position",atoi(n));
        FREEXMLBUFF(n);
    }

    n=FROMXMLCAST(xmlGetProp(root,TOXMLCAST("disabled")));
    if(n)
    {
        setStr("disabled",n);
        FREEXMLBUFF(n);
    }

    n=FROMXMLCAST(xmlGetProp(root,TOXMLCAST("action")));
    if(n)
    {
        setAction(string(n));
        FREEXMLBUFF(n);
    }

    n=FROMXMLCAST(xmlGetProp(root,TOXMLCAST("log")));
    if(n)
    {
        setStr("log",n);
        FREEXMLBUFF(n);
    }


    n=FROMXMLCAST(xmlGetProp(root,TOXMLCAST("interface")));
    if(n)
    {
        setStr("interface",n);
        FREEXMLBUFF(n);
    }

    n= FROMXMLCAST(xmlGetProp(root,TOXMLCAST("direction")));
    if(n)
    {
        setDirection(string(n));
        FREEXMLBUFF(n);
    }

    n= FROMXMLCAST(xmlGetProp(root,TOXMLCAST("group")));
    if(n)
    {
        setStr("group",n);
        FREEXMLBUFF(n);
    }

}

xmlNodePtr PolicyRule::toXML(xmlNodePtr parent) throw(FWException)
{
    xmlNodePtr me = FWObject::toXML(parent, false);
    xmlNewProp(me, TOXMLCAST("action"), STRTOXMLCAST(getActionAsString()));
    xmlNewProp(me, TOXMLCAST("direction"),STRTOXMLCAST(getDirectionAsString()));
    xmlNewProp(me, TOXMLCAST("comment"), STRTOXMLCAST(getComment()));

    FWObject *o;

    /*
     * Save children to XML file in just this order (src, dst, srv).
     * PolicyCompiler::checkForShadowing depends on it!
     * But after all, DTD requires this order.
     *
     <!ELEMENT PolicyRule (Src,Dst,Srv?,Itf?,When?,PolicyRuleOptions?)>
     */
    if ( (o=getFirstByType( RuleElementSrc::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RuleElementDst::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RuleElementSrv::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RuleElementItf::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RuleElementInterval::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( PolicyRuleOptions::TYPENAME ))!=NULL )
	o->toXML(me);

    // there should be no children Policy objects in v3
    if ( (o=getFirstByType( Policy::TYPENAME ))!=NULL )
	o->toXML(me);

    return me;
}

FWOptions* PolicyRule::getOptionsObject()
{
    return FWOptions::cast( getFirstByType(PolicyRuleOptions::TYPENAME) );
}

RuleSet*   PolicyRule::getBranch()
{
    FWObject *fw = this;
    while (fw && !Firewall::isA(fw)) fw = fw->getParent();
    assert(fw!=NULL);
    string branch_id = getOptionsObject()->getStr("branch_id");
    if (!branch_id.empty())
    {
        return RuleSet::cast(getRoot()->findInIndex(
                                 FWObjectDatabase::getIntId(branch_id)));
    } else
    {
        string branch_name = getOptionsObject()->getStr("branch_name");
        if (!branch_name.empty())
        {
            return RuleSet::cast(
                fw->findObjectByName(Policy::TYPENAME, branch_name));
        } else
            return NULL;
    }
}

void PolicyRule::setBranch(RuleSet* ruleset)
{
    string branch_id = 
        (ruleset) ? FWObjectDatabase::getStringId(ruleset->getId()) : "";
    getOptionsObject()->setStr("branch_id", branch_id);
}

void PolicyRule::setTagObject(FWObject *tag_object)
{
    string tag_id =
        (tag_object) ? FWObjectDatabase::getStringId(tag_object->getId()) : "";
    getOptionsObject()->setStr("tagobject_id", tag_id);
}

FWObject* PolicyRule::getTagObject()
{
    if (getAction() == Tag)
    {
        string tagobj_id = getOptionsObject()->getStr("tagobject_id");
        if (!tagobj_id.empty())
        {
            return getRoot()->findInIndex(
                FWObjectDatabase::getIntId(tagobj_id));
        }
    }
    return NULL;
}

string PolicyRule::getTagValue()
{
    if (getAction() == Tag)
    {
        TagService *tagobj = TagService::cast(getTagObject());
        if (tagobj)  return tagobj->getCode();
        else         return getOptionsObject()->getStr("tagvalue");
    }
    return "";
}

/**
 * Removes reference to given object among children of 'this'. In case
 * of PolicyRule we should also clear reference to it if action is
 * Branch. Caveat: clear reference to it even if action is not branch
 * right now but was in the past and reference got stuck in options.
 *
 * Do the same for the TagService
 */
void PolicyRule::removeRef(FWObject *obj)
{
    if (RuleSet::cast(obj))
    {
        string branch_id = FWObjectDatabase::getStringId(obj->getId());
        string rule_branch_id = getOptionsObject()->getStr("branch_id");
        if (branch_id == rule_branch_id)
            getOptionsObject()->setStr("branch_id", "");
    }

    if (TagService::cast(obj))
    {
        string tag_id = FWObjectDatabase::getStringId(obj->getId());
        string rule_tag_id = getOptionsObject()->getStr("tagobject_id");
        if (tag_id == rule_tag_id)
            getOptionsObject()->setStr("tagobject_id", "");
    }

    FWObject::removeRef(obj);
}

/***************************************************************************/

const char *NATRule::TYPENAME={"NATRule"};

NATRule::NATRule() : Rule()
{
    rule_type=Unknown;

    osrc_re = NULL;
    odst_re = NULL;
    osrv_re = NULL;
    tsrc_re = NULL;
    tdst_re = NULL;
    tsrv_re = NULL;
    when_re = NULL;
}

NATRule::NATRule(const FWObjectDatabase *root,bool prepopulate) : Rule(root,prepopulate)
{
    rule_type=Unknown;

    osrc_re = NULL;
    odst_re = NULL;
    osrv_re = NULL;
    tsrc_re = NULL;
    tdst_re = NULL;
    tsrv_re = NULL;
    when_re = NULL;

    if (prepopulate)
    {
        FWObject         *re;
        FWObjectDatabase *db=(FWObjectDatabase*)(root);
        assert(db);

        re = db->createRuleElementOSrc();  assert(re!=NULL); add(re);
        re = db->createRuleElementODst();  assert(re!=NULL); add(re);
        re = db->createRuleElementOSrv();  assert(re!=NULL); add(re);

        re = db->createRuleElementTSrc();  assert(re!=NULL); add(re);
        re = db->createRuleElementTDst();  assert(re!=NULL); add(re);
        re = db->createRuleElementTSrv();  assert(re!=NULL); add(re);

        add( db->createNATRuleOptions() );
    }
}

RuleElementOSrc*  NATRule::getOSrc()
{
    if (osrc_re) return osrc_re;
    osrc_re = RuleElementOSrc::cast(getFirstByType(RuleElementOSrc::TYPENAME));
    return osrc_re;
}

RuleElementODst*  NATRule::getODst()
{
    if (odst_re) return odst_re;
    odst_re = RuleElementODst::cast(getFirstByType(RuleElementODst::TYPENAME));
    return odst_re;
}

RuleElementOSrv*  NATRule::getOSrv()
{
    if (osrv_re) return osrv_re;
    osrv_re = RuleElementOSrv::cast(getFirstByType(RuleElementOSrv::TYPENAME));
    return osrv_re;
}

RuleElementTSrc*  NATRule::getTSrc()
{
    if (tsrc_re) return tsrc_re;
    tsrc_re = RuleElementTSrc::cast(getFirstByType(RuleElementTSrc::TYPENAME));
    return tsrc_re;
}

RuleElementTDst*  NATRule::getTDst()
{
    if (tdst_re) return tdst_re;
    tdst_re = RuleElementTDst::cast(getFirstByType(RuleElementTDst::TYPENAME));
    return tdst_re;
}

RuleElementTSrv*  NATRule::getTSrv()
{
    if (tsrv_re) return tsrv_re;
    tsrv_re = RuleElementTSrv::cast(getFirstByType(RuleElementTSrv::TYPENAME));
    return tsrv_re;
}

RuleElementInterval* NATRule::getWhen()
{
    if (when_re) return when_re;
    when_re = RuleElementInterval::cast(getFirstByType(RuleElementInterval::TYPENAME));
    return when_re;
}

bool NATRule::isEmpty()
{
    RuleElement *osrc=getOSrc();
    RuleElement *odst=getODst();
    RuleElement *osrv=getOSrv();

    RuleElement *tsrc=getTSrc();
    RuleElement *tdst=getTDst();
    RuleElement *tsrv=getTSrv();

    return (osrc->isAny() && odst->isAny() && osrv->isAny() && tsrc->isAny() && tdst->isAny() && tsrv->isAny());
}

void NATRule::fromXML(xmlNodePtr root) throw(FWException)
{
    const char* n;

    FWObject::fromXML(root);

    n=FROMXMLCAST(xmlGetProp(root,TOXMLCAST("disabled")));
    if(n)
    {
        setStr("disabled",n);
        FREEXMLBUFF(n);
    }

    n=FROMXMLCAST(xmlGetProp(root,TOXMLCAST("position")));
    if(n)
    {
        setStr("position",n);
        FREEXMLBUFF(n);
    }

    n= FROMXMLCAST(xmlGetProp(root,TOXMLCAST("group")));
    if(n)
    {
        setStr("group",n);
        FREEXMLBUFF(n);
    }

}

xmlNodePtr NATRule::toXML(xmlNodePtr parent) throw(FWException)
{
    xmlNodePtr me = FWObject::toXML(parent, false);
//    xmlNewProp(me, TOXMLCAST("name"), STRTOXMLCAST(getName()));
    xmlNewProp(me, TOXMLCAST("comment"), STRTOXMLCAST(getComment()));

    FWObject *o;

    if ( (o=getFirstByType( RuleElementOSrc::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RuleElementODst::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RuleElementOSrv::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RuleElementTSrc::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RuleElementTDst::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RuleElementTSrv::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RuleElementInterval::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( NATRuleOptions::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( NAT::TYPENAME ))!=NULL )
	o->toXML(me);

    return me;
}

FWOptions* NATRule::getOptionsObject()
{
    return FWOptions::cast( getFirstByType(NATRuleOptions::TYPENAME) );
}

RuleSet*   NATRule::getBranch()
{
    FWObject *fw = getParent()->getParent();
    assert(fw!=NULL);
    string branch_id = getOptionsObject()->getStr("branch_id");
    if (!branch_id.empty())
    {
        return RuleSet::cast(getRoot()->findInIndex(
                                 FWObjectDatabase::getIntId(branch_id)));
    } else
    {
        string branch_name = getOptionsObject()->getStr("branch_name");
        if (!branch_name.empty())
            return RuleSet::cast(fw->findObjectByName(NAT::TYPENAME,
                                                  branch_name));
        else
            return NULL;
    }
}

void NATRule::setBranch(RuleSet* ruleset)
{
    string branch_id = 
        (ruleset) ? FWObjectDatabase::getStringId(ruleset->getId()) : "";
    getOptionsObject()->setStr("branch_id", branch_id);
}

NATRule::NATRuleTypes NATRule::getRuleType() const
{ 
    return rule_type;
}

string  NATRule::getRuleTypeAsString() const 
{
    switch (rule_type) {
    case SNAT:     return("SNAT");     
    case DNAT:     return("DNAT");     
    case SDNAT:    return("SDNAT");     
    case Masq:     return("Masq");     
    case SNetnat:  return("SNetnat");  
    case DNetnat:  return("DNetnat");  
    case Redirect: return("Redirect"); 
    case Return:   return("Return");   
    case Skip:     return("Skip");     
    case Continue: return("Continue"); 
    case LB:       return("LB");       
    case NONAT:    return("NONAT");    
    default:       return("Unknown");  
    }
}

void         NATRule::setRuleType(NATRuleTypes rt) 
{ 
    rule_type=rt;
}

FWObject& NATRule::shallowDuplicate(const FWObject *x,
                                    bool preserve_id) throw(FWException)
{
    const NATRule *rx=NATRule::constcast(x);
    if (rx!=NULL) rule_type=rx->rule_type;

    osrc_re = NULL;
    odst_re = NULL;
    osrv_re = NULL;
    tsrc_re = NULL;
    tdst_re = NULL;
    tsrv_re = NULL;
    when_re = NULL;

    return  Rule::shallowDuplicate(x, preserve_id);
}



/***************************************************************************/

const char *RoutingRule::TYPENAME={"RoutingRule"};

RoutingRule::RoutingRule() : Rule()
{
    rule_type=Undefined;
    sorted_dst_ids="";
    setMetric(0);
}

RoutingRule::RoutingRule(const FWObjectDatabase *root,bool prepopulate) : Rule(root,prepopulate)
{
    if (prepopulate)
    {
        FWObject         *re;
        FWObjectDatabase *db=(FWObjectDatabase*)(root);
        assert(db);

        re = db->createRuleElementRDst();  assert(re!=NULL); add(re);
        re = db->createRuleElementRGtw();  assert(re!=NULL); add(re);
        re = db->createRuleElementRItf();  assert(re!=NULL); add(re);
    
        setMetric(0);

        add( db->createRoutingRuleOptions() );
    }
}

RuleElementRDst*  RoutingRule::getRDst()  const
{
    return RuleElementRDst::cast(getFirstByType(RuleElementRDst::TYPENAME));
}

RuleElementRGtw*  RoutingRule::getRGtw()  const
{
    return RuleElementRGtw::cast(getFirstByType(RuleElementRGtw::TYPENAME));
}

RuleElementRItf*  RoutingRule::getRItf()  const
{
    return RuleElementRItf::cast(getFirstByType(RuleElementRItf::TYPENAME));
}


bool RoutingRule::isEmpty() const
{
    RuleElement *rdst=getRDst();
    RuleElement *rgtw=getRGtw();
    RuleElement *ritf=getRItf();

    return (rdst->isAny() && rgtw->isAny() && ritf->isAny());
}

int RoutingRule::getMetric() const {
    return getInt("metric");
}

string RoutingRule::getMetricAsString() const {
    
    stringstream s; 
    s << getMetric();
  
    return s.str();
}

void RoutingRule::setMetric(const int metric) {
    setInt("metric", metric);
}

void RoutingRule::setMetric(string metric) {
    
    int imetric = atoi(metric.c_str());
    setInt("metric", imetric);
}

void RoutingRule::fromXML(xmlNodePtr root) throw(FWException)
{
    const char* n;

    FWObject::fromXML(root);

    n=FROMXMLCAST(xmlGetProp(root,TOXMLCAST("disabled")));
    if(n)
    {
        setStr("disabled",n);
        FREEXMLBUFF(n);
    }

    n=FROMXMLCAST(xmlGetProp(root,TOXMLCAST("metric")));
    if(n)
    {
        setStr("metric",n);
        FREEXMLBUFF(n);
    }

    n=FROMXMLCAST(xmlGetProp(root,TOXMLCAST("position")));
    if(n)
    {
        setStr("position",n);
        FREEXMLBUFF(n);
    }

    n= FROMXMLCAST(xmlGetProp(root,TOXMLCAST("group")));
    if(n)
    {
        setStr("group",n);
        FREEXMLBUFF(n);
    }

}

xmlNodePtr RoutingRule::toXML(xmlNodePtr parent) throw(FWException)
{
    xmlNodePtr me = FWObject::toXML(parent, false);
//    xmlNewProp(me, TOXMLCAST("name"), STRTOXMLCAST(getName()));
    xmlNewProp(me, TOXMLCAST("comment"), STRTOXMLCAST(getComment()));

    FWObject *o;

    if ( (o=getFirstByType( RuleElementRDst::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RuleElementRGtw::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RuleElementRItf::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( RoutingRuleOptions::TYPENAME ))!=NULL )
	o->toXML(me);

    if ( (o=getFirstByType( Routing::TYPENAME ))!=NULL )
	o->toXML(me);

    return me;
}

FWOptions* RoutingRule::getOptionsObject()
{
    return FWOptions::cast( getFirstByType(RoutingRuleOptions::TYPENAME) );
}

RuleSet*   RoutingRule::getBranch()
{
    FWObject *fw = getParent()->getParent();
    assert(fw!=NULL);
    string branch_id = getOptionsObject()->getStr("branch_id");
    if (!branch_id.empty())
    {
        return RuleSet::cast(getRoot()->findInIndex(
                                 FWObjectDatabase::getIntId(branch_id)));
    } else
    {
        string branch_name = getOptionsObject()->getStr("branch_name");
        if (!branch_name.empty())
            return RuleSet::cast(fw->findObjectByName(Routing::TYPENAME,
                                                      branch_name));
        else
            return NULL;
    }
}

RoutingRule::RoutingRuleTypes RoutingRule::getRuleType() const
{ 
    return rule_type;
}

string  RoutingRule::getRuleTypeAsString() const 
{
    switch (rule_type) {
    case Undefined:   return("Undefined");
    case SinglePath:  return("Single Path");     
    case MultiPath:   return("Multi Path");        
    default:          return("Unknown");  
    }
}

void RoutingRule::setRuleType(RoutingRuleTypes rt) 
{ 
    rule_type=rt;
}

FWObject& RoutingRule::duplicate(const FWObject *x,
                                 bool preserve_id) throw(FWException)
{
    Rule::duplicate(x,preserve_id);
    const RoutingRule *rx = RoutingRule::constcast(x);
    if (rx!=NULL)
    {
        rule_type = rx->rule_type;
        sorted_dst_ids = rx->sorted_dst_ids;
    }
    return *this;
}

void RoutingRule::setSortedDstIds(const string& ids)
{
    sorted_dst_ids = ids;
}

string RoutingRule::getSortedDstIds() const
{
    return sorted_dst_ids;
}
