/* $ANTLR 2.7.7 (20090306): "pix.g" -> "PIXCfgParser.cpp"$ */
#line 40 "pix.g"

    // gets inserted before the antlr generated includes in the cpp
    // file

#line 8 "PIXCfgParser.cpp"
#include "PIXCfgParser.hpp"
#include <antlr/NoViableAltException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/ASTFactory.hpp>
#line 46 "pix.g"

    // gets inserted after the antlr generated includes in the cpp
    // file
#include <antlr/Token.hpp>
#include <antlr/TokenBuffer.hpp>

#include "PIXImporter.h"

#line 22 "PIXCfgParser.cpp"
#line 1 "pix.g"
#line 24 "PIXCfgParser.cpp"
PIXCfgParser::PIXCfgParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,k)
{
}

PIXCfgParser::PIXCfgParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,2)
{
}

PIXCfgParser::PIXCfgParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,k)
{
}

PIXCfgParser::PIXCfgParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,2)
{
}

PIXCfgParser::PIXCfgParser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(state,2)
{
}

void PIXCfgParser::cfgfile() {
	
	try {      // for error handling
		{ // ( ... )+
		int _cnt3=0;
		for (;;) {
			switch ( LA(1)) {
			case LINE_COMMENT:
			case COLON_COMMENT:
			{
				comment();
				break;
			}
			case PIX_WORD:
			case ASA_WORD:
			{
				version();
				break;
			}
			case HOSTNAME:
			{
				hostname();
				break;
			}
			case INTRFACE:
			{
				intrface();
				break;
			}
			case CONTROLLER:
			{
				controller();
				break;
			}
			case ACCESS_LIST:
			{
				access_list_commands();
				break;
			}
			case EXIT:
			{
				exit();
				break;
			}
			case CERTIFICATE:
			{
				certificate();
				break;
			}
			case QUIT:
			{
				quit();
				break;
			}
			case NAMES:
			{
				names_section();
				break;
			}
			case NAME:
			case IPV6:
			{
				name_entry();
				break;
			}
			case CRYPTO:
			{
				crypto();
				break;
			}
			case WORD:
			{
				unknown_command();
				break;
			}
			case NEWLINE:
			{
				match(NEWLINE);
				break;
			}
			default:
				if ((LA(1) == IP) && (LA(2) == ACCESS_LIST)) {
					ip_access_list_ext();
				}
				else if ((LA(1) == IP) && (LA(2) == COMMUNITY_LIST)) {
					community_list_command();
				}
				else if ((LA(1) == IP) && (LA(2) == WORD)) {
					unknown_ip_command();
				}
				else if ((LA(1) == OBJECT) && (LA(2) == NETWORK)) {
					named_object_network();
				}
				else if ((LA(1) == OBJECT) && (LA(2) == SERVICE)) {
					named_object_service();
				}
				else if ((LA(1) == OBJECT_GROUP) && (LA(2) == NETWORK)) {
					object_group_network();
				}
				else if ((LA(1) == OBJECT_GROUP) && (LA(2) == SERVICE)) {
					object_group_service();
				}
				else if ((LA(1) == OBJECT_GROUP) && (LA(2) == PROTOCOL)) {
					object_group_protocol();
				}
				else if ((LA(1) == OBJECT_GROUP) && (LA(2) == ICMP_OBJECT)) {
					object_group_icmp_8_0();
				}
				else if ((LA(1) == OBJECT_GROUP) && (LA(2) == ICMP_TYPE)) {
					object_group_icmp_8_3();
				}
			else {
				if ( _cnt3>=1 ) { goto _loop3; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			}
			_cnt3++;
		}
		_loop3:;
		}  // ( ... )+
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::comment() {
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case LINE_COMMENT:
		{
			match(LINE_COMMENT);
			break;
		}
		case COLON_COMMENT:
		{
			match(COLON_COMMENT);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::version() {
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case PIX_WORD:
		{
			match(PIX_WORD);
			break;
		}
		case ASA_WORD:
		{
			match(ASA_WORD);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		match(VERSION_WORD);
		match(NUMBER);
		if ( inputState->guessing==0 ) {
#line 722 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->setDiscoveredVersion(LT(0)->getText());
			*dbg << "VERSION " << LT(0)->getText() << std::endl;
			consumeUntil(NEWLINE);
			
#line 243 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::hostname() {
	
	try {      // for error handling
		match(HOSTNAME);
		{
		switch ( LA(1)) {
		case STRING:
		{
			match(STRING);
			break;
		}
		case WORD:
		{
			match(WORD);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 732 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->setHostName( LT(0)->getText() );
			*dbg << "HOSTNAME "
			<< "LT0=" << LT(0)->getText()
			<< std::endl;
			
#line 287 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::ip_access_list_ext() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(IP);
		match(ACCESS_LIST);
		name = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 768 "pix.g"
			
			importer->clear();
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newUnidirRuleSet(
			name->getText(), libfwbuilder::Policy::TYPENAME );
			*dbg << name->getLine() << ":"
			<< " ACL ext " << name->getText() << std::endl;
			
#line 318 "PIXCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case PERMIT:
		{
			permit_ext();
			break;
		}
		case DENY:
		{
			deny_ext();
			break;
		}
		case LINE_COMMENT:
		case COLON_COMMENT:
		{
			comment();
			break;
		}
		case REMARK:
		{
			remark();
			break;
		}
		case NEWLINE:
		{
			match(NEWLINE);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 787 "pix.g"
			
			*dbg << LT(0)->getLine() << ":"
			<< " ACL line end" << std::endl << std::endl;
			
#line 360 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::community_list_command() {
	
	try {      // for error handling
		match(IP);
		match(COMMUNITY_LIST);
		if ( inputState->guessing==0 ) {
#line 144 "pix.g"
			
			consumeUntil(NEWLINE);
			
#line 383 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::unknown_ip_command() {
	
	try {      // for error handling
		match(IP);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 700 "pix.g"
			
			consumeUntil(NEWLINE);
			
#line 406 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::intrface() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  in = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(INTRFACE);
		in = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 1049 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newInterface( in->getText() );
			*dbg << in->getLine() << ":"
			<< " INTRFACE: " << in->getText() << std::endl;
			consumeUntil(NEWLINE);
			
#line 435 "PIXCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case DESCRIPTION:
		{
			interface_description();
			break;
		}
		case NEWLINE:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		{ // ( ... )+
		int _cnt149=0;
		for (;;) {
			if ((LA(1) == NEWLINE) && (_tokenSet_2.member(LA(2)))) {
				interface_parameters();
			}
			else {
				if ( _cnt149>=1 ) { goto _loop149; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt149++;
		}
		_loop149:;
		}  // ( ... )+
		match(NEWLINE);
		match(LINE_COMMENT);
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::controller() {
	
	try {      // for error handling
		match(CONTROLLER);
		if ( inputState->guessing==0 ) {
#line 1003 "pix.g"
			
			importer->clearCurrentInterface();
			consumeUntil(NEWLINE);
			
#line 491 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::access_list_commands() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  acl_num = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(ACCESS_LIST);
		acl_num = LT(1);
		match(INT_CONST);
		if ( inputState->guessing==0 ) {
#line 748 "pix.g"
			
			importer->clear();
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newUnidirRuleSet( std::string("acl_") + acl_num->getText(),
			libfwbuilder::Policy::TYPENAME );
			*dbg << acl_num->getLine() << ":"
			<< " ACL #" << acl_num->getText() << " ";
			
#line 521 "PIXCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case PERMIT:
		{
			permit_ext();
			break;
		}
		case DENY:
		{
			deny_ext();
			break;
		}
		case REMARK:
		{
			remark();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::exit() {
	
	try {      // for error handling
		match(EXIT);
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::certificate() {
	
	try {      // for error handling
		match(CERTIFICATE);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 714 "pix.g"
			
			consumeUntil(NEWLINE);
			consumeUntil(QUIT);
			
#line 583 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::quit() {
	
	try {      // for error handling
		match(QUIT);
		if ( inputState->guessing==0 ) {
#line 137 "pix.g"
			
			consumeUntil(NEWLINE);
			
#line 605 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::names_section() {
	
	try {      // for error handling
		match(NAMES);
		if ( inputState->guessing==0 ) {
#line 151 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->addMessageToLog(
			"Parser warning: \"names\" section detected. "
			"Import of configuration that uses \"names\" "
			"is not supported at this time");
			
#line 631 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::name_entry() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  a = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  n = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  v6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		switch ( LA(1)) {
		case NAME:
		{
			match(NAME);
			{
			a = LT(1);
			match(IPV4);
			n = LT(1);
			match(WORD);
			}
			break;
		}
		case IPV6:
		{
			{
			v6 = LT(1);
			match(IPV6);
			}
			if ( inputState->guessing==0 ) {
#line 161 "pix.g"
				
				if (a)
				{
				importer->setCurrentLineNumber(LT(0)->getLine());
				importer->addMessageToLog(
				"Name " + a->getText() + " " + n->getText());
				*dbg << "Name " << a->getText() << " " << n->getText() << std::endl;
				}
				if (v6)
				{
				importer->addMessageToLog(
				"Parser warning: IPv6 import is not supported. ");
				consumeUntil(NEWLINE);
				}
				
#line 685 "PIXCfgParser.cpp"
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::named_object_network() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(OBJECT);
		match(NETWORK);
		name = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 194 "pix.g"
			
			importer->clear();
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newNamedObjectAddress(name->getText());
			*dbg << name->getLine() << ":"
			<< " Named Object " << name->getText() << std::endl;
			
#line 722 "PIXCfgParser.cpp"
		}
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == NEWLINE) && ((LA(2) >= NAT && LA(2) <= SUBNET))) {
				match(NEWLINE);
				named_object_network_parameters();
			}
			else {
				goto _loop14;
			}
			
		}
		_loop14:;
		} // ( ... )*
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::named_object_service() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(OBJECT);
		match(SERVICE);
		name = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 304 "pix.g"
			
			importer->clear();
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newNamedObjectService(name->getText());
			*dbg << name->getLine() << ":"
			<< " Named Object " << name->getText() << std::endl;
			
#line 765 "PIXCfgParser.cpp"
		}
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == NEWLINE) && (LA(2) == DESCRIPTION || LA(2) == SERVICE)) {
				match(NEWLINE);
				named_object_service_parameters();
			}
			else {
				goto _loop30;
			}
			
		}
		_loop30:;
		} // ( ... )*
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::object_group_network() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(OBJECT_GROUP);
		match(NETWORK);
		name = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 398 "pix.g"
			
			importer->clear();
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newObjectGroupNetwork(name->getText());
			*dbg << name->getLine() << ":"
			<< " Object Group " << name->getText() << std::endl;
			
#line 808 "PIXCfgParser.cpp"
		}
		{ // ( ... )+
		int _cnt48=0;
		for (;;) {
			if ((LA(1) == NEWLINE) && (LA(2) == DESCRIPTION || LA(2) == GROUP_OBJECT || LA(2) == NETWORK_OBJECT)) {
				object_group_network_parameters();
			}
			else {
				if ( _cnt48>=1 ) { goto _loop48; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt48++;
		}
		_loop48:;
		}  // ( ... )+
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::object_group_service() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(OBJECT_GROUP);
		match(SERVICE);
		name = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 619 "pix.g"
			
			importer->clear();
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newObjectGroupService(name->getText());
			*dbg << name->getLine() << ":"
			<< " Object Group " << name->getText() << std::endl;
			
#line 852 "PIXCfgParser.cpp"
		}
		{ // ( ... )+
		int _cnt79=0;
		for (;;) {
			if ((LA(1) == NEWLINE) && (LA(2) == DESCRIPTION || LA(2) == GROUP_OBJECT || LA(2) == SERVICE_OBJECT)) {
				object_group_service_parameters();
			}
			else {
				if ( _cnt79>=1 ) { goto _loop79; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt79++;
		}
		_loop79:;
		}  // ( ... )+
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::object_group_protocol() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(OBJECT_GROUP);
		match(PROTOCOL);
		name = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 496 "pix.g"
			
			importer->clear();
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newObjectGroupProtocol(name->getText());
			*dbg << name->getLine() << ":"
			<< " Object Group " << name->getText() << std::endl;
			
#line 896 "PIXCfgParser.cpp"
		}
		{ // ( ... )+
		int _cnt60=0;
		for (;;) {
			if ((LA(1) == NEWLINE) && (LA(2) == DESCRIPTION || LA(2) == GROUP_OBJECT || LA(2) == PROTOCOL_OBJECT)) {
				object_group_protocol_parameters();
			}
			else {
				if ( _cnt60>=1 ) { goto _loop60; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt60++;
		}
		_loop60:;
		}  // ( ... )+
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::object_group_icmp_8_0() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(OBJECT_GROUP);
		match(ICMP_OBJECT);
		name = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 551 "pix.g"
			
			importer->clear();
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newObjectGroupICMP(name->getText());
			*dbg << name->getLine() << ":"
			<< " Object Group " << name->getText() << std::endl;
			
#line 940 "PIXCfgParser.cpp"
		}
		{ // ( ... )+
		int _cnt68=0;
		for (;;) {
			if ((LA(1) == NEWLINE) && (LA(2) == DESCRIPTION || LA(2) == GROUP_OBJECT || LA(2) == ICMP_OBJECT)) {
				object_group_icmp_parameters();
			}
			else {
				if ( _cnt68>=1 ) { goto _loop68; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt68++;
		}
		_loop68:;
		}  // ( ... )+
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::object_group_icmp_8_3() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(OBJECT_GROUP);
		match(ICMP_TYPE);
		name = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 564 "pix.g"
			
			importer->clear();
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newObjectGroupICMP(name->getText());
			*dbg << name->getLine() << ":"
			<< " Object Group " << name->getText() << std::endl;
			
#line 984 "PIXCfgParser.cpp"
		}
		{ // ( ... )+
		int _cnt71=0;
		for (;;) {
			if ((LA(1) == NEWLINE) && (LA(2) == DESCRIPTION || LA(2) == GROUP_OBJECT || LA(2) == ICMP_OBJECT)) {
				object_group_icmp_parameters();
			}
			else {
				if ( _cnt71>=1 ) { goto _loop71; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt71++;
		}
		_loop71:;
		}  // ( ... )+
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::crypto() {
	
	try {      // for error handling
		match(CRYPTO);
		if ( inputState->guessing==0 ) {
#line 693 "pix.g"
			
			consumeUntil(NEWLINE);
			
#line 1020 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::unknown_command() {
	
	try {      // for error handling
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 707 "pix.g"
			
			consumeUntil(NEWLINE);
			
#line 1042 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::ip_protocol_names() {
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case AH:
		{
			match(AH);
			break;
		}
		case EIGRP:
		{
			match(EIGRP);
			break;
		}
		case ESP:
		{
			match(ESP);
			break;
		}
		case GRE:
		{
			match(GRE);
			break;
		}
		case IGMP:
		{
			match(IGMP);
			break;
		}
		case IGRP:
		{
			match(IGRP);
			break;
		}
		case IP:
		{
			match(IP);
			break;
		}
		case IPINIP:
		{
			match(IPINIP);
			break;
		}
		case IPSEC:
		{
			match(IPSEC);
			break;
		}
		case NOS:
		{
			match(NOS);
			break;
		}
		case OSPF:
		{
			match(OSPF);
			break;
		}
		case PCP:
		{
			match(PCP);
			break;
		}
		case PIM:
		{
			match(PIM);
			break;
		}
		case PPTP:
		{
			match(PPTP);
			break;
		}
		case SNP:
		{
			match(SNP);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::named_object_network_parameters() {
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case NAT:
		{
			named_object_nat();
			break;
		}
		case HOST:
		{
			host_addr();
			break;
		}
		case RANGE:
		{
			range_addr();
			break;
		}
		case SUBNET:
		{
			subnet_addr();
			break;
		}
		case DESCRIPTION:
		{
			named_object_description();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::named_object_nat() {
	
	try {      // for error handling
		match(NAT);
		if ( inputState->guessing==0 ) {
#line 222 "pix.g"
			
			importer->addMessageToLog(
			"Parser warning: "
			"Import of named objects with \"nat\" command "
			"is not supported at this time");
			consumeUntil(NEWLINE);
			
#line 1212 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::host_addr() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  h = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  v6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		{
		match(HOST);
		{
		switch ( LA(1)) {
		case IPV4:
		{
			h = LT(1);
			match(IPV4);
			break;
		}
		case IPV6:
		{
			v6 = LT(1);
			match(IPV6);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 253 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			if (h)
			{
			importer->tmp_a = h->getText();
			importer->tmp_nm = "255.255.255.255";
			importer->commitNamedAddressObject();
			*dbg << h->getText() << "/255.255.255.255";
			}
			if (v6)
			{
			importer->addMessageToLog(
			"Parser warning: IPv6 import is not supported. ");
			consumeUntil(NEWLINE);
			}
			
#line 1271 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::range_addr() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  r1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  r2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		{
		match(RANGE);
		r1 = LT(1);
		match(IPV4);
		r2 = LT(1);
		match(IPV4);
		}
		if ( inputState->guessing==0 ) {
#line 272 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->tmp_range_1 = r1->getText();
			importer->tmp_range_2 = r2->getText();
			importer->commitNamedAddressRangeObject();
			*dbg << r1->getText() << "/" << r2->getText();
			
#line 1305 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::subnet_addr() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  a = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  nm = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  v6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		{
		match(SUBNET);
		{
		switch ( LA(1)) {
		case IPV4:
		{
			{
			a = LT(1);
			match(IPV4);
			nm = LT(1);
			match(IPV4);
			}
			break;
		}
		case IPV6:
		{
			v6 = LT(1);
			match(IPV6);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 282 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			if (a)
			{
			importer->tmp_a = a->getText();
			importer->tmp_nm = nm->getText();
			importer->commitNamedAddressObject();
			*dbg << a->getText() << "/" << nm->getText();
			}
			if (v6)
			{
			importer->addMessageToLog(
			"Parser warning: IPv6 import is not supported. ");
			consumeUntil(NEWLINE);
			}
			
#line 1369 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::named_object_description() {
	
	try {      // for error handling
		match(DESCRIPTION);
		if ( inputState->guessing==0 ) {
#line 232 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			*dbg << LT(1)->getLine() << ":";
			std::string descr;
			while (LA(1) != ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE && LA(1) != NEWLINE)
			{
			descr += LT(1)->getText() + " ";
			consume();
			}
			importer->setNamedObjectDescription(descr);
			*dbg << " DESCRIPTION " << descr << std::endl;
			
#line 1400 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::named_object_service_parameters() {
	
	try {      // for error handling
		{
		if ((LA(1) == SERVICE) && (LA(2) == ICMP)) {
			service_icmp();
		}
		else if ((LA(1) == SERVICE) && (LA(2) == ICMP6)) {
			service_icmp6();
		}
		else if ((LA(1) == SERVICE) && (LA(2) == TCP || LA(2) == UDP)) {
			service_tcp_udp();
		}
		else if ((LA(1) == SERVICE) && (_tokenSet_4.member(LA(2)))) {
			service_other();
		}
		else if ((LA(1) == DESCRIPTION)) {
			named_object_description();
		}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::service_icmp() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  icmp_type = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  icmp_word = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(SERVICE);
		match(ICMP);
		{
		switch ( LA(1)) {
		case INT_CONST:
		{
			icmp_type = LT(1);
			match(INT_CONST);
			if ( inputState->guessing==0 ) {
#line 334 "pix.g"
				
				importer->icmp_type = LT(0)->getText();
				
#line 1466 "PIXCfgParser.cpp"
			}
			break;
		}
		case WORD:
		{
			icmp_word = LT(1);
			match(WORD);
			if ( inputState->guessing==0 ) {
#line 338 "pix.g"
				
				importer->icmp_spec = icmp_word->getText();
				
#line 1479 "PIXCfgParser.cpp"
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 342 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->commitNamedICMPServiceObject();
			*dbg << "NAMED OBJECT SERVICE ICMP " << LT(0)->getText() << " ";
			
#line 1496 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::service_icmp6() {
	
	try {      // for error handling
		match(SERVICE);
		match(ICMP6);
		{
		switch ( LA(1)) {
		case INT_CONST:
		{
			match(INT_CONST);
			break;
		}
		case WORD:
		{
			match(WORD);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 350 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->addMessageToLog("Parser warning: "
			"Import of IPv6 addresses and servcies "
			"is not supported at this time");
			*dbg << "NAMED OBJECT SERVICE ICMP6 " << LT(0)->getText() << " ";
			consumeUntil(NEWLINE);
			
#line 1542 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::service_tcp_udp() {
	
	try {      // for error handling
		match(SERVICE);
		{
		switch ( LA(1)) {
		case TCP:
		{
			match(TCP);
			break;
		}
		case UDP:
		{
			match(UDP);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 361 "pix.g"
			
			importer->protocol = LT(0)->getText();
			*dbg << "NAMED OBJECT SERVICE " << LT(0)->getText() << " ";
			
#line 1583 "PIXCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case SOURCE:
		{
			src_port_spec();
			break;
		}
		case ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE:
		case NEWLINE:
		case QUIT:
		case IP:
		case NAMES:
		case NAME:
		case WORD:
		case IPV6:
		case OBJECT:
		case RANGE:
		case DESTINATION:
		case OBJECT_GROUP:
		case CRYPTO:
		case CERTIFICATE:
		case PIX_WORD:
		case ASA_WORD:
		case HOSTNAME:
		case ACCESS_LIST:
		case P_EQ:
		case P_GT:
		case P_LT:
		case P_NEQ:
		case CONTROLLER:
		case INTRFACE:
		case LINE_COMMENT:
		case EXIT:
		case COLON_COMMENT:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		{
		switch ( LA(1)) {
		case RANGE:
		case DESTINATION:
		case P_EQ:
		case P_GT:
		case P_LT:
		case P_NEQ:
		{
			dst_port_spec();
			break;
		}
		case ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE:
		case NEWLINE:
		case QUIT:
		case IP:
		case NAMES:
		case NAME:
		case WORD:
		case IPV6:
		case OBJECT:
		case OBJECT_GROUP:
		case CRYPTO:
		case CERTIFICATE:
		case PIX_WORD:
		case ASA_WORD:
		case HOSTNAME:
		case ACCESS_LIST:
		case CONTROLLER:
		case INTRFACE:
		case LINE_COMMENT:
		case EXIT:
		case COLON_COMMENT:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 367 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->commitNamedTCPUDPServiceObject();
			
#line 1676 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::service_other() {
	
	try {      // for error handling
		match(SERVICE);
		{
		switch ( LA(1)) {
		case INT_CONST:
		{
			match(INT_CONST);
			break;
		}
		case IP:
		case AH:
		case EIGRP:
		case ESP:
		case GRE:
		case IGMP:
		case IGRP:
		case IPINIP:
		case IPSEC:
		case NOS:
		case OSPF:
		case PCP:
		case PIM:
		case PPTP:
		case SNP:
		{
			ip_protocol_names();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 386 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->protocol = LT(0)->getText();
			importer->commitNamedIPServiceObject();
			*dbg << "NAMED OBJECT SERVICE " << LT(0)->getText() << " ";
			
#line 1733 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::src_port_spec() {
	
	try {      // for error handling
		match(SOURCE);
		xoperator();
		if ( inputState->guessing==0 ) {
#line 374 "pix.g"
			
			importer->SaveTmpPortToSrc();
			
#line 1756 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::dst_port_spec() {
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case DESTINATION:
		{
			match(DESTINATION);
			break;
		}
		case RANGE:
		case P_EQ:
		case P_GT:
		case P_LT:
		case P_NEQ:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		xoperator();
		if ( inputState->guessing==0 ) {
#line 380 "pix.g"
			
			importer->SaveTmpPortToDst();
			
#line 1799 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::xoperator() {
	
	try {      // for error handling
		switch ( LA(1)) {
		case P_EQ:
		case P_GT:
		case P_LT:
		case P_NEQ:
		{
			single_port_op();
			break;
		}
		case RANGE:
		{
			port_range();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::object_group_network_parameters() {
	
	try {      // for error handling
		match(NEWLINE);
		{
		switch ( LA(1)) {
		case DESCRIPTION:
		{
			object_group_description();
			break;
		}
		case GROUP_OBJECT:
		{
			group_object();
			break;
		}
		case NETWORK_OBJECT:
		{
			network_object();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::object_group_description() {
	
	try {      // for error handling
		match(DESCRIPTION);
		if ( inputState->guessing==0 ) {
#line 422 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			*dbg << LT(1)->getLine() << ":";
			std::string descr;
			while (LA(1) != ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE && LA(1) != NEWLINE)
			{
			descr += LT(1)->getText() + " ";
			consume();
			}
			importer->setObjectGroupDescription(descr);
			*dbg << " DESCRIPTION " << descr << std::endl;
			
#line 1901 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::group_object() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(GROUP_OBJECT);
		name = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 437 "pix.g"
			
			importer->clearTempVars();
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->addNamedObjectToObjectGroup(name->getText());
			*dbg << " GROUP MEMBER " << name->getLine() << std::endl;
			
#line 1929 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::network_object() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  a = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  nm = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  v6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  h = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  hv6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(NETWORK_OBJECT);
		if ( inputState->guessing==0 ) {
#line 446 "pix.g"
			
			importer->clearTempVars();
			importer->setCurrentLineNumber(LT(0)->getLine());
			
#line 1958 "PIXCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case IPV4:
		case IPV6:
		{
			{
			switch ( LA(1)) {
			case IPV4:
			{
				{
				a = LT(1);
				match(IPV4);
				nm = LT(1);
				match(IPV4);
				}
				break;
			}
			case IPV6:
			{
				v6 = LT(1);
				match(IPV6);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 452 "pix.g"
				
				if (a)
				{
				importer->tmp_a = a->getText();
				importer->tmp_nm = nm->getText();
				importer->addNetworkToObjectGroup();
				*dbg << a->getText() << "/" << nm->getText();
				}
				if (v6)
				{
				importer->addMessageToLog(
				"Parser warning: IPv6 import is not supported. ");
				consumeUntil(NEWLINE);
				}
				
#line 2006 "PIXCfgParser.cpp"
			}
			break;
		}
		case HOST:
		{
			match(HOST);
			{
			switch ( LA(1)) {
			case IPV4:
			{
				h = LT(1);
				match(IPV4);
				break;
			}
			case IPV6:
			{
				hv6 = LT(1);
				match(IPV6);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 469 "pix.g"
				
				if (h)
				{
				importer->tmp_a = h->getText();
				importer->tmp_nm = "255.255.255.255";
				importer->addNetworkToObjectGroup();
				*dbg << h->getText() << "/255.255.255.255";
				}
				if (hv6)
				{
				importer->addMessageToLog(
				"Parser warning: IPv6 import is not supported. ");
				consumeUntil(NEWLINE);
				}
				
#line 2050 "PIXCfgParser.cpp"
			}
			break;
		}
		case OBJECT:
		{
			match(OBJECT);
			name = LT(1);
			match(WORD);
			if ( inputState->guessing==0 ) {
#line 486 "pix.g"
				
				importer->addNamedObjectToObjectGroup(name->getText());
				*dbg << " GROUP MEMBER " << name->getLine() << std::endl;
				
#line 2065 "PIXCfgParser.cpp"
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::object_group_protocol_parameters() {
	
	try {      // for error handling
		match(NEWLINE);
		{
		switch ( LA(1)) {
		case DESCRIPTION:
		{
			object_group_description();
			break;
		}
		case GROUP_OBJECT:
		{
			group_object();
			break;
		}
		case PROTOCOL_OBJECT:
		{
			protocol_object();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::protocol_object() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(PROTOCOL_OBJECT);
		if ( inputState->guessing==0 ) {
#line 520 "pix.g"
			
			importer->clearTempVars();
			importer->setCurrentLineNumber(LT(0)->getLine());
			
#line 2135 "PIXCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case IP:
		case AH:
		case EIGRP:
		case ESP:
		case GRE:
		case IGMP:
		case IGRP:
		case IPINIP:
		case IPSEC:
		case NOS:
		case OSPF:
		case PCP:
		case PIM:
		case PPTP:
		case SNP:
		case ICMP:
		case INT_CONST:
		case TCP:
		case UDP:
		{
			{
			switch ( LA(1)) {
			case INT_CONST:
			{
				match(INT_CONST);
				break;
			}
			case ICMP:
			{
				match(ICMP);
				break;
			}
			case TCP:
			{
				match(TCP);
				break;
			}
			case UDP:
			{
				match(UDP);
				break;
			}
			case IP:
			case AH:
			case EIGRP:
			case ESP:
			case GRE:
			case IGMP:
			case IGRP:
			case IPINIP:
			case IPSEC:
			case NOS:
			case OSPF:
			case PCP:
			case PIM:
			case PPTP:
			case SNP:
			{
				ip_protocol_names();
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 526 "pix.g"
				
				importer->setCurrentLineNumber(LT(0)->getLine());
				importer->protocol = LT(0)->getText();
				importer->addIPServiceToObjectGroup();
				*dbg << " GROUP MEMBER " << LT(0)->getText() << " ";
				
#line 2214 "PIXCfgParser.cpp"
			}
			break;
		}
		case ICMP6:
		{
			match(ICMP6);
			if ( inputState->guessing==0 ) {
#line 534 "pix.g"
				
				importer->addMessageToLog(
				"Parser warning: IPv6 import is not supported. ");
				consumeUntil(NEWLINE);
				
#line 2228 "PIXCfgParser.cpp"
			}
			break;
		}
		case OBJECT:
		{
			match(OBJECT);
			name = LT(1);
			match(WORD);
			if ( inputState->guessing==0 ) {
#line 541 "pix.g"
				
				importer->addNamedObjectToObjectGroup(name->getText());
				*dbg << " GROUP MEMBER " << name->getLine() << std::endl;
				
#line 2243 "PIXCfgParser.cpp"
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::object_group_icmp_parameters() {
	
	try {      // for error handling
		match(NEWLINE);
		{
		switch ( LA(1)) {
		case DESCRIPTION:
		{
			object_group_description();
			break;
		}
		case GROUP_OBJECT:
		{
			group_object();
			break;
		}
		case ICMP_OBJECT:
		{
			icmp_object();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::icmp_object() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  icmp_type = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  icmp_word = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(ICMP_OBJECT);
		if ( inputState->guessing==0 ) {
#line 588 "pix.g"
			
			importer->clearTempVars();
			importer->setCurrentLineNumber(LT(0)->getLine());
			
#line 2315 "PIXCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case WORD:
		case INT_CONST:
		{
			{
			switch ( LA(1)) {
			case INT_CONST:
			{
				icmp_type = LT(1);
				match(INT_CONST);
				if ( inputState->guessing==0 ) {
#line 595 "pix.g"
					
					importer->icmp_type = LT(0)->getText();
					
#line 2333 "PIXCfgParser.cpp"
				}
				break;
			}
			case WORD:
			{
				icmp_word = LT(1);
				match(WORD);
				if ( inputState->guessing==0 ) {
#line 599 "pix.g"
					
					importer->icmp_spec = icmp_word->getText();
					
#line 2346 "PIXCfgParser.cpp"
				}
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 603 "pix.g"
				
				importer->addICMPServiceToObjectGroup();
				*dbg << " SERVICE ICMP " << LT(0)->getText() << " ";
				
#line 2362 "PIXCfgParser.cpp"
			}
			break;
		}
		case OBJECT:
		{
			match(OBJECT);
			name = LT(1);
			match(WORD);
			if ( inputState->guessing==0 ) {
#line 609 "pix.g"
				
				importer->addNamedObjectToObjectGroup(name->getText());
				*dbg << " GROUP MEMBER " << name->getLine() << std::endl;
				
#line 2377 "PIXCfgParser.cpp"
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::object_group_service_parameters() {
	
	try {      // for error handling
		match(NEWLINE);
		{
		switch ( LA(1)) {
		case DESCRIPTION:
		{
			object_group_description();
			break;
		}
		case GROUP_OBJECT:
		{
			group_object();
			break;
		}
		case SERVICE_OBJECT:
		{
			service_object();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::service_object() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  icmp_type = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  icmp_word = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(SERVICE_OBJECT);
		if ( inputState->guessing==0 ) {
#line 643 "pix.g"
			
			importer->clearTempVars();
			importer->setCurrentLineNumber(LT(0)->getLine());
			
#line 2449 "PIXCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case IP:
		case AH:
		case EIGRP:
		case ESP:
		case GRE:
		case IGMP:
		case IGRP:
		case IPINIP:
		case IPSEC:
		case NOS:
		case OSPF:
		case PCP:
		case PIM:
		case PPTP:
		case SNP:
		case INT_CONST:
		{
			{
			switch ( LA(1)) {
			case INT_CONST:
			{
				match(INT_CONST);
				break;
			}
			case IP:
			case AH:
			case EIGRP:
			case ESP:
			case GRE:
			case IGMP:
			case IGRP:
			case IPINIP:
			case IPSEC:
			case NOS:
			case OSPF:
			case PCP:
			case PIM:
			case PPTP:
			case SNP:
			{
				ip_protocol_names();
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 649 "pix.g"
				
				importer->setCurrentLineNumber(LT(0)->getLine());
				importer->protocol = LT(0)->getText();
				importer->addIPServiceToObjectGroup();
				*dbg << " GROUP MEMBER " << LT(0)->getText() << " ";
				
#line 2510 "PIXCfgParser.cpp"
			}
			break;
		}
		case TCP:
		case UDP:
		{
			{
			switch ( LA(1)) {
			case TCP:
			{
				match(TCP);
				break;
			}
			case UDP:
			{
				match(UDP);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 657 "pix.g"
				
				importer->protocol = LT(0)->getText();
				*dbg << " SERVICE TCP/UDP" << LT(0)->getText() << " ";
				
#line 2541 "PIXCfgParser.cpp"
			}
			{
			switch ( LA(1)) {
			case SOURCE:
			{
				src_port_spec();
				break;
			}
			case ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE:
			case NEWLINE:
			case QUIT:
			case IP:
			case NAMES:
			case NAME:
			case WORD:
			case IPV6:
			case OBJECT:
			case RANGE:
			case DESTINATION:
			case OBJECT_GROUP:
			case CRYPTO:
			case CERTIFICATE:
			case PIX_WORD:
			case ASA_WORD:
			case HOSTNAME:
			case ACCESS_LIST:
			case P_EQ:
			case P_GT:
			case P_LT:
			case P_NEQ:
			case CONTROLLER:
			case INTRFACE:
			case LINE_COMMENT:
			case EXIT:
			case COLON_COMMENT:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case RANGE:
			case DESTINATION:
			case P_EQ:
			case P_GT:
			case P_LT:
			case P_NEQ:
			{
				dst_port_spec();
				break;
			}
			case ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE:
			case NEWLINE:
			case QUIT:
			case IP:
			case NAMES:
			case NAME:
			case WORD:
			case IPV6:
			case OBJECT:
			case OBJECT_GROUP:
			case CRYPTO:
			case CERTIFICATE:
			case PIX_WORD:
			case ASA_WORD:
			case HOSTNAME:
			case ACCESS_LIST:
			case CONTROLLER:
			case INTRFACE:
			case LINE_COMMENT:
			case EXIT:
			case COLON_COMMENT:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 663 "pix.g"
				
				importer->addTCPUDPServiceToObjectGroup();
				
#line 2633 "PIXCfgParser.cpp"
			}
			break;
		}
		case ICMP:
		{
			match(ICMP);
			{
			switch ( LA(1)) {
			case INT_CONST:
			{
				icmp_type = LT(1);
				match(INT_CONST);
				if ( inputState->guessing==0 ) {
#line 670 "pix.g"
					
					importer->icmp_type = LT(0)->getText();
					
#line 2651 "PIXCfgParser.cpp"
				}
				break;
			}
			case WORD:
			{
				icmp_word = LT(1);
				match(WORD);
				if ( inputState->guessing==0 ) {
#line 674 "pix.g"
					
					importer->icmp_spec = icmp_word->getText();
					
#line 2664 "PIXCfgParser.cpp"
				}
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 678 "pix.g"
				
				importer->addICMPServiceToObjectGroup();
				*dbg << " SERVICE ICMP " << LT(0)->getText() << " ";
				
#line 2680 "PIXCfgParser.cpp"
			}
			break;
		}
		case OBJECT:
		{
			match(OBJECT);
			name = LT(1);
			match(WORD);
			if ( inputState->guessing==0 ) {
#line 684 "pix.g"
				
				importer->addNamedObjectToObjectGroup(name->getText());
				*dbg << " GROUP MEMBER " << name->getLine() << std::endl;
				
#line 2695 "PIXCfgParser.cpp"
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::permit_ext() {
	
	try {      // for error handling
		match(PERMIT);
		if ( inputState->guessing==0 ) {
#line 795 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newPolicyRule();
			importer->action = "permit";
			*dbg << LT(1)->getLine() << ":" << " permit ";
			
#line 2728 "PIXCfgParser.cpp"
		}
		rule_ext();
		match(NEWLINE);
		if ( inputState->guessing==0 ) {
#line 802 "pix.g"
			
			importer->pushRule();
			
#line 2737 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::deny_ext() {
	
	try {      // for error handling
		match(DENY);
		if ( inputState->guessing==0 ) {
#line 808 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->newPolicyRule();
			importer->action = "deny";
			*dbg << LT(1)->getLine() << ":" << " deny   ";
			
#line 2762 "PIXCfgParser.cpp"
		}
		rule_ext();
		match(NEWLINE);
		if ( inputState->guessing==0 ) {
#line 815 "pix.g"
			
			importer->pushRule();
			
#line 2771 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::remark() {
	
	try {      // for error handling
		match(REMARK);
		if ( inputState->guessing==0 ) {
#line 1303 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			*dbg << LT(1)->getLine() << ":";
			std::string rem;
			while (LA(1) != ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE && LA(1) != NEWLINE)
			{
			rem += LT(1)->getText() + " ";
			consume();
			}
			importer->addRuleComment( rem );
			*dbg << " REMARK " << rem << std::endl;
			//consumeUntil(NEWLINE);
			
#line 2803 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::rule_ext() {
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case IP:
		case AH:
		case EIGRP:
		case ESP:
		case GRE:
		case IGMP:
		case IGRP:
		case IPINIP:
		case IPSEC:
		case NOS:
		case OSPF:
		case PCP:
		case PIM:
		case PPTP:
		case SNP:
		{
			ip_protocols();
			hostaddr_ext();
			if ( inputState->guessing==0 ) {
#line 825 "pix.g"
				importer->SaveTmpAddrToSrc(); *dbg << "(src) ";
#line 2842 "PIXCfgParser.cpp"
			}
			hostaddr_ext();
			if ( inputState->guessing==0 ) {
#line 826 "pix.g"
				importer->SaveTmpAddrToDst(); *dbg << "(dst) ";
#line 2848 "PIXCfgParser.cpp"
			}
			{
			switch ( LA(1)) {
			case TIME_RANGE:
			{
				time_range();
				break;
			}
			case NEWLINE:
			case LOG:
			case LOG_INPUT:
			case FRAGMENTS:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case FRAGMENTS:
			{
				fragments();
				break;
			}
			case NEWLINE:
			case LOG:
			case LOG_INPUT:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case LOG:
			case LOG_INPUT:
			{
				log();
				break;
			}
			case NEWLINE:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			break;
		}
		case ICMP:
		{
			match(ICMP);
			if ( inputState->guessing==0 ) {
#line 832 "pix.g"
				
				importer->protocol = LT(0)->getText();
				*dbg << "protocol " << LT(0)->getText() << " ";
				
#line 2918 "PIXCfgParser.cpp"
			}
			hostaddr_ext();
			if ( inputState->guessing==0 ) {
#line 836 "pix.g"
				importer->SaveTmpAddrToSrc(); *dbg << "(src) ";
#line 2924 "PIXCfgParser.cpp"
			}
			hostaddr_ext();
			if ( inputState->guessing==0 ) {
#line 837 "pix.g"
				importer->SaveTmpAddrToDst(); *dbg << "(dst) ";
#line 2930 "PIXCfgParser.cpp"
			}
			{
			switch ( LA(1)) {
			case WORD:
			case INT_CONST:
			{
				icmp_spec();
				break;
			}
			case NEWLINE:
			case LOG:
			case LOG_INPUT:
			case FRAGMENTS:
			case TIME_RANGE:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case TIME_RANGE:
			{
				time_range();
				break;
			}
			case NEWLINE:
			case LOG:
			case LOG_INPUT:
			case FRAGMENTS:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case FRAGMENTS:
			{
				fragments();
				break;
			}
			case NEWLINE:
			case LOG:
			case LOG_INPUT:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case LOG:
			case LOG_INPUT:
			{
				log();
				break;
			}
			case NEWLINE:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			break;
		}
		case TCP:
		case UDP:
		{
			{
			switch ( LA(1)) {
			case TCP:
			{
				match(TCP);
				break;
			}
			case UDP:
			{
				match(UDP);
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 844 "pix.g"
				
				importer->protocol = LT(0)->getText();
				*dbg << "protocol " << LT(0)->getText() << " ";
				
#line 3040 "PIXCfgParser.cpp"
			}
			hostaddr_ext();
			if ( inputState->guessing==0 ) {
#line 848 "pix.g"
				importer->SaveTmpAddrToSrc(); *dbg << "(src) ";
#line 3046 "PIXCfgParser.cpp"
			}
			{
			switch ( LA(1)) {
			case RANGE:
			case P_EQ:
			case P_GT:
			case P_LT:
			case P_NEQ:
			{
				xoperator();
				if ( inputState->guessing==0 ) {
#line 849 "pix.g"
					importer->SaveTmpPortToSrc();
#line 3060 "PIXCfgParser.cpp"
				}
				break;
			}
			case IPV4:
			case HOST:
			case ANY:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			hostaddr_ext();
			if ( inputState->guessing==0 ) {
#line 850 "pix.g"
				importer->SaveTmpAddrToDst(); *dbg << "(dst) ";
#line 3080 "PIXCfgParser.cpp"
			}
			{
			switch ( LA(1)) {
			case RANGE:
			case P_EQ:
			case P_GT:
			case P_LT:
			case P_NEQ:
			{
				xoperator();
				if ( inputState->guessing==0 ) {
#line 851 "pix.g"
					importer->SaveTmpPortToDst();
#line 3094 "PIXCfgParser.cpp"
				}
				break;
			}
			case NEWLINE:
			case LOG:
			case LOG_INPUT:
			case ESTABLISHED:
			case FRAGMENTS:
			case TIME_RANGE:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case ESTABLISHED:
			{
				established();
				break;
			}
			case NEWLINE:
			case LOG:
			case LOG_INPUT:
			case FRAGMENTS:
			case TIME_RANGE:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case TIME_RANGE:
			{
				time_range();
				break;
			}
			case NEWLINE:
			case LOG:
			case LOG_INPUT:
			case FRAGMENTS:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case FRAGMENTS:
			{
				fragments();
				break;
			}
			case NEWLINE:
			case LOG:
			case LOG_INPUT:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case LOG:
			case LOG_INPUT:
			{
				log();
				break;
			}
			case NEWLINE:
			{
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 857 "pix.g"
			
			*dbg << std::endl;
			
#line 3204 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::ip_protocols() {
	
	try {      // for error handling
		ip_protocol_names();
		if ( inputState->guessing==0 ) {
#line 864 "pix.g"
			
			importer->protocol = LT(0)->getText();
			*dbg << "protocol " << LT(0)->getText() << " ";
			
#line 3227 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_8);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::hostaddr_ext() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  h = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  a = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  m = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		switch ( LA(1)) {
		case HOST:
		{
			{
			match(HOST);
			h = LT(1);
			match(IPV4);
			}
			if ( inputState->guessing==0 ) {
#line 927 "pix.g"
				
				importer->tmp_a = h->getText();
				importer->tmp_nm = "255.255.255.255";
				*dbg << h->getText() << "/255.255.255.255";
				
#line 3261 "PIXCfgParser.cpp"
			}
			break;
		}
		case IPV4:
		{
			{
			a = LT(1);
			match(IPV4);
			m = LT(1);
			match(IPV4);
			}
			if ( inputState->guessing==0 ) {
#line 934 "pix.g"
				
				importer->tmp_a = a->getText();
				importer->tmp_nm = m->getText();
				*dbg << a->getText() << "/" << m->getText();
				
#line 3280 "PIXCfgParser.cpp"
			}
			break;
		}
		case ANY:
		{
			match(ANY);
			if ( inputState->guessing==0 ) {
#line 941 "pix.g"
				
				importer->tmp_a = "0.0.0.0";
				importer->tmp_nm = "0.0.0.0";
				*dbg << "0.0.0.0/0.0.0.0";
				
#line 3294 "PIXCfgParser.cpp"
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_9);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::time_range() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  tr_name = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(TIME_RANGE);
		tr_name = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 993 "pix.g"
			
			importer->time_range_name = tr_name->getText();
			*dbg << "time_range " << tr_name->getText() << " ";
			
#line 3327 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_10);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::fragments() {
	
	try {      // for error handling
		match(FRAGMENTS);
		if ( inputState->guessing==0 ) {
#line 986 "pix.g"
			
			importer->fragments = true;
			*dbg << "fragments ";
			
#line 3350 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_11);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::log() {
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case LOG:
		{
			match(LOG);
			break;
		}
		case LOG_INPUT:
		{
			match(LOG_INPUT);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 972 "pix.g"
			
			importer->logging = true;
			*dbg << "logging ";
			
#line 3390 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::icmp_spec() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  icmp_type = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  icmp_code = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  icmp_word = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case INT_CONST:
		{
			{
			icmp_type = LT(1);
			match(INT_CONST);
			icmp_code = LT(1);
			match(INT_CONST);
			}
			if ( inputState->guessing==0 ) {
#line 872 "pix.g"
				
				importer->icmp_type = icmp_type->getText();
				importer->icmp_code = icmp_code->getText();
				importer->icmp_spec = "";
				*dbg << icmp_type->getText() << " "
				<< icmp_code->getText() << " ";
				
#line 3428 "PIXCfgParser.cpp"
			}
			break;
		}
		case WORD:
		{
			icmp_word = LT(1);
			match(WORD);
			if ( inputState->guessing==0 ) {
#line 881 "pix.g"
				
				importer->icmp_spec = icmp_word->getText();
				*dbg << icmp_word->getText() << " ";
				
#line 3442 "PIXCfgParser.cpp"
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_12);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::established() {
	
	try {      // for error handling
		match(ESTABLISHED);
		if ( inputState->guessing==0 ) {
#line 979 "pix.g"
			
			importer->established = true;
			*dbg << "established ";
			
#line 3473 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_12);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::single_port_op() {
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case P_EQ:
		{
			match(P_EQ);
			break;
		}
		case P_GT:
		{
			match(P_GT);
			break;
		}
		case P_LT:
		{
			match(P_LT);
			break;
		}
		case P_NEQ:
		{
			match(P_NEQ);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 892 "pix.g"
			
			importer->tmp_port_op = LT(0)->getText();
			*dbg << LT(0)->getText() << " ";
			
#line 3523 "PIXCfgParser.cpp"
		}
		port_spec();
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::port_range() {
	
	try {      // for error handling
		match(RANGE);
		pair_of_ports_spec();
		if ( inputState->guessing==0 ) {
#line 907 "pix.g"
			
			importer->tmp_port_op = "range";
			*dbg << "range ";
			
#line 3548 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::port_spec() {
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case WORD:
		{
			match(WORD);
			break;
		}
		case INT_CONST:
		{
			match(INT_CONST);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 900 "pix.g"
			
			importer->tmp_port_spec = (std::string(" ") + LT(0)->getText());
			*dbg << LT(0)->getText() << " " << importer->tmp_port_spec;
			
#line 3588 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::pair_of_ports_spec() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  s1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  s2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  e1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  e2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case WORD:
		{
			s1 = LT(1);
			match(WORD);
			break;
		}
		case INT_CONST:
		{
			s2 = LT(1);
			match(INT_CONST);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		{
		switch ( LA(1)) {
		case WORD:
		{
			e1 = LT(1);
			match(WORD);
			break;
		}
		case INT_CONST:
		{
			e2 = LT(1);
			match(INT_CONST);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 914 "pix.g"
			
			importer->tmp_port_spec = "";
			if (s1) importer->tmp_port_spec += s1->getText();
			if (s2) importer->tmp_port_spec += s2->getText();
			importer->tmp_port_spec += " ";
			if (e1) importer->tmp_port_spec += e1->getText();
			if (e2) importer->tmp_port_spec += e2->getText();
			*dbg << "pair of ports: " << importer->tmp_port_spec;
			
#line 3659 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::hostaddr_std() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  h = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  a = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  m = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		if ((LA(1) == IPV4) && (LA(2) == ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE)) {
			{
			h = LT(1);
			match(IPV4);
			}
			if ( inputState->guessing==0 ) {
#line 950 "pix.g"
				
				importer->tmp_a = h->getText();
				importer->tmp_nm = "0.0.0.0";
				*dbg << h->getText() << "/0.0.0.0";
				
#line 3690 "PIXCfgParser.cpp"
			}
		}
		else if ((LA(1) == IPV4) && (LA(2) == IPV4)) {
			{
			a = LT(1);
			match(IPV4);
			m = LT(1);
			match(IPV4);
			}
			if ( inputState->guessing==0 ) {
#line 957 "pix.g"
				
				importer->tmp_a = a->getText();
				importer->tmp_nm = m->getText();
				*dbg << a->getText() << "/" << m->getText();
				
#line 3707 "PIXCfgParser.cpp"
			}
		}
		else if ((LA(1) == ANY)) {
			match(ANY);
			if ( inputState->guessing==0 ) {
#line 964 "pix.g"
				
				importer->tmp_a = "0.0.0.0";
				importer->tmp_nm = "0.0.0.0";
				*dbg << "0.0.0.0/0.0.0.0";
				
#line 3719 "PIXCfgParser.cpp"
			}
		}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::interface_description() {
	
	try {      // for error handling
		match(DESCRIPTION);
		if ( inputState->guessing==0 ) {
#line 1179 "pix.g"
			
			*dbg << LT(1)->getLine() << ":";
			std::string descr;
			while (LA(1) != ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE && LA(1) != NEWLINE)
			{
			descr += LT(1)->getText() + " ";
			consume();
			}
			importer->setInterfaceComment( descr );
			*dbg << " DESCRIPTION " << descr << std::endl;
			//consumeUntil(NEWLINE);
			
#line 3755 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::interface_parameters() {
	
	try {      // for error handling
		match(NEWLINE);
		if ( inputState->guessing==0 ) {
#line 1067 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			
#line 3777 "PIXCfgParser.cpp"
		}
		{
		switch ( LA(1)) {
		case IP:
		{
			intf_address();
			break;
		}
		case VLAN:
		{
			vlan_interface();
			break;
		}
		case SEC_LEVEL:
		{
			sec_level();
			break;
		}
		case NAMEIF:
		{
			nameif();
			break;
		}
		case DESCRIPTION:
		{
			interface_description();
			break;
		}
		case SWITCHPORT:
		{
			switchport();
			break;
		}
		case SHUTDOWN:
		{
			shutdown();
			break;
		}
		case NO:
		{
			interface_no_commands();
			break;
		}
		case IGMP:
		case OSPF:
		case PIM:
		case SPEED:
		case DUPLEX:
		case DDNS:
		case FORWARD:
		case DELAY:
		case HOLD_TIME:
		case IPV6_C:
		case MAC_ADDRESS:
		case MULTICAST:
		case PPPOE:
		case RIP:
		{
			unsupported_interface_commands();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::intf_address() {
	
	try {      // for error handling
		match(IP);
		match(ADDRESS);
		{
		switch ( LA(1)) {
		case WORD:
		{
			v6_ip_address();
			break;
		}
		case IPV4:
		case DHCP:
		{
			v7_ip_address();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::vlan_interface() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  vlan_id = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(VLAN);
		vlan_id = LT(1);
		match(INT_CONST);
		if ( inputState->guessing==0 ) {
#line 1092 "pix.g"
			
			importer->setInterfaceVlanId(vlan_id->getText());
			*dbg << " VLAN: " << vlan_id->getText() << std::endl;
			
#line 3904 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::sec_level() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  sec_level = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(SEC_LEVEL);
		sec_level = LT(1);
		match(INT_CONST);
		if ( inputState->guessing==0 ) {
#line 1144 "pix.g"
			
			importer->setInterfaceSecurityLevel(sec_level->getText());
			*dbg << "SEC_LEVEL: " << sec_level->getText() << std::endl;
			
#line 3930 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::nameif() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  p_intf = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  intf_label = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  sec_level = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(NAMEIF);
		p_intf = LT(1);
		match(WORD);
		{
		switch ( LA(1)) {
		case WORD:
		{
			intf_label = LT(1);
			match(WORD);
			sec_level = LT(1);
			match(WORD);
			break;
		}
		case NEWLINE:
		{
			{
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 1167 "pix.g"
			
			std::string label = (intf_label) ? intf_label->getText() : "";
			std::string seclevel = (sec_level) ? sec_level->getText() : "";
			importer->setInterfaceParametes(p_intf->getText(), label, seclevel);
			*dbg << " NAMEIF: "
			<< p_intf->getText() << label << seclevel << std::endl;
			
#line 3983 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::switchport() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  vlan_num = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(SWITCHPORT);
		match(ACCESS);
		match(VLAN);
		vlan_num = LT(1);
		match(INT_CONST);
		if ( inputState->guessing==0 ) {
#line 1291 "pix.g"
			
			importer->addMessageToLog("Switch port vlan " + vlan_num->getText());
			*dbg << "Switch port vlan " <<  vlan_num->getText() << std::endl;
			
#line 4011 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::shutdown() {
	
	try {      // for error handling
		match(SHUTDOWN);
		if ( inputState->guessing==0 ) {
#line 1194 "pix.g"
			
			importer->ignoreCurrentInterface();
			*dbg<< LT(1)->getLine() << ":"
			<< " INTERFACE SHUTDOWN " << std::endl;
			
#line 4035 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::interface_no_commands() {
	
	try {      // for error handling
		match(NO);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 1136 "pix.g"
			
			*dbg << " INTERFACE \"NO\" COMMAND: "
			<< LT(0)->getText() << std::endl;
			consumeUntil(NEWLINE);
			
#line 4060 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::unsupported_interface_commands() {
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case SPEED:
		{
			match(SPEED);
			break;
		}
		case DUPLEX:
		{
			match(DUPLEX);
			break;
		}
		case DDNS:
		{
			match(DDNS);
			break;
		}
		case FORWARD:
		{
			match(FORWARD);
			break;
		}
		case DELAY:
		{
			match(DELAY);
			break;
		}
		case HOLD_TIME:
		{
			match(HOLD_TIME);
			break;
		}
		case IGMP:
		{
			match(IGMP);
			break;
		}
		case IPV6_C:
		{
			match(IPV6_C);
			break;
		}
		case MAC_ADDRESS:
		{
			match(MAC_ADDRESS);
			break;
		}
		case MULTICAST:
		{
			match(MULTICAST);
			break;
		}
		case OSPF:
		{
			match(OSPF);
			break;
		}
		case PIM:
		{
			match(PIM);
			break;
		}
		case PPPOE:
		{
			match(PPPOE);
			break;
		}
		case RIP:
		{
			match(RIP);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 1128 "pix.g"
			
			*dbg << " UNSUPPORTED INTERFACE COMMAND: "
			<< LT(0)->getText() << std::endl;
			consumeUntil(NEWLINE);
			
#line 4161 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::v6_ip_address() {
	
	try {      // for error handling
		if ((LA(1) == WORD) && (LA(2) == DHCP)) {
			v6_dhcp_address();
		}
		else if ((LA(1) == WORD) && (LA(2) == IPV4)) {
			v6_static_address();
		}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::v7_ip_address() {
	
	try {      // for error handling
		switch ( LA(1)) {
		case DHCP:
		{
			v7_dhcp_address();
			break;
		}
		case IPV4:
		{
			v7_static_address();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::v6_dhcp_address() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  lbl = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  dhcp = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		lbl = LT(1);
		match(WORD);
		dhcp = LT(1);
		match(DHCP);
		if ( inputState->guessing==0 ) {
#line 1229 "pix.g"
			
			std::string label = lbl->getText();
			std::string addr = dhcp->getText();
			importer->addInterfaceAddress(label, addr, "");
			*dbg << LT(1)->getLine() << ":"
			<< " INTRFACE ADDRESS: " << addr << std::endl;
			// there can be some other parameters after "dhcp", such as "setroute", "retry" etc.
			// which we do not support
			consumeUntil(NEWLINE);
			
#line 4249 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::v6_static_address() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  lbl = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  a = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  m = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		lbl = LT(1);
		match(WORD);
		a = LT(1);
		match(IPV4);
		m = LT(1);
		match(IPV4);
		if ( inputState->guessing==0 ) {
#line 1242 "pix.g"
			
			std::string label = lbl->getText();
			std::string addr = a->getText();
			std::string netm = m->getText();
			importer->addInterfaceAddress(label, addr, netm);
			*dbg << LT(1)->getLine() << ":"
			<< " INTRFACE ADDRESS: " << addr << "/" << netm << std::endl;
			// in case there are some other parameters after address and netmask
			consumeUntil(NEWLINE);
			
#line 4286 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::v7_dhcp_address() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  dhcp = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		dhcp = LT(1);
		match(DHCP);
		if ( inputState->guessing==0 ) {
#line 1259 "pix.g"
			
			std::string addr = dhcp->getText();
			importer->addInterfaceAddress(addr, "");
			*dbg << LT(1)->getLine() << ":"
			<< " INTRFACE ADDRESS: " << addr << std::endl;
			consumeUntil(NEWLINE);
			
#line 4314 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::v7_static_address() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  a = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  m = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  s = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		a = LT(1);
		match(IPV4);
		m = LT(1);
		match(IPV4);
		{
		switch ( LA(1)) {
		case STANDBY:
		{
			s = LT(1);
			match(STANDBY);
			break;
		}
		case NEWLINE:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 1270 "pix.g"
			
			std::string addr = a->getText();
			std::string netm = m->getText();
			importer->addInterfaceAddress(addr, netm);
			*dbg << LT(1)->getLine() << ":"
			<< " INTRFACE ADDRESS: " << addr << "/" << netm << std::endl;
			// there can be other parameters after address/netmask pair, such as "standby"
			// We do not parse them yet.
			if (s)
			{
			importer->addMessageToLog("Parser warning: failover IP detected. "
			"Failover is not supported by import "
			"at this time");
			}
			consumeUntil(NEWLINE);
			
#line 4373 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::access_group_by_name() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  acln = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  dir = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  intf_label = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	try {      // for error handling
		match(ACCESS_GROUP);
		acln = LT(1);
		match(WORD);
		dir = LT(1);
		match(WORD);
		match(INTRFACE);
		intf_label = LT(1);
		match(WORD);
		if ( inputState->guessing==0 ) {
#line 1321 "pix.g"
			
			importer->setCurrentLineNumber(LT(0)->getLine());
			importer->setInterfaceAndDirectionForRuleSet(
			acln->getText(),
			intf_label->getText(),
			dir->getText() );
			*dbg << LT(1)->getLine() << ":"
			<< " INTRFACE: ACL '" << acln->getText() << "'"
			<< " " << intf_label->getText()
			<< " " << dir->getText() << std::endl;
			
#line 4413 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		} else {
			throw;
		}
	}
}

void PIXCfgParser::initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& )
{
}
const char* PIXCfgParser::tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"NEWLINE",
	"\"quit\"",
	"\"ip\"",
	"\"community-list\"",
	"\"names\"",
	"\"name\"",
	"IPV4",
	"WORD",
	"IPV6",
	"\"ah\"",
	"\"eigrp\"",
	"\"esp\"",
	"\"gre\"",
	"\"igmp\"",
	"\"igrp\"",
	"\"ipinip\"",
	"IPSEC",
	"\"nos\"",
	"\"ospf\"",
	"\"pcp\"",
	"\"pim\"",
	"PPTP",
	"\"snp\"",
	"\"object\"",
	"\"network\"",
	"\"nat\"",
	"\"description\"",
	"\"host\"",
	"\"range\"",
	"\"subnet\"",
	"\"service\"",
	"\"icmp\"",
	"INT_CONST",
	"\"icmp6\"",
	"\"tcp\"",
	"\"udp\"",
	"\"source\"",
	"\"destination\"",
	"\"object-group\"",
	"\"group-object\"",
	"\"network-object\"",
	"\"protocol\"",
	"\"protocol-object\"",
	"\"icmp-object\"",
	"\"icmp-type\"",
	"\"service-object\"",
	"\"crypto\"",
	"\"certificate\"",
	"\"PIX\"",
	"\"ASA\"",
	"\"Version\"",
	"NUMBER",
	"\"hostname\"",
	"STRING",
	"\"access-list\"",
	"\"permit\"",
	"\"deny\"",
	"\"eq\"",
	"\"gt\"",
	"\"lt\"",
	"\"neq\"",
	"\"any\"",
	"\"log\"",
	"\"log-input\"",
	"\"established\"",
	"\"fragments\"",
	"\"time-range\"",
	"\"controller\"",
	"\"interface\"",
	"LINE_COMMENT",
	"\"vlan\"",
	"\"speed\"",
	"\"duplex\"",
	"\"ddns\"",
	"\"forward\"",
	"\"delay\"",
	"\"hold-time\"",
	"\"ipv6\"",
	"\"mac-address\"",
	"\"multicast\"",
	"PPPOE",
	"\"rip\"",
	"\"no\"",
	"\"security-level\"",
	"\"nameif\"",
	"\"shutdown\"",
	"\"address\"",
	"\"dhcp\"",
	"\"standby\"",
	"\"switchport\"",
	"\"access\"",
	"\"remark\"",
	"\"access-group\"",
	"\"exit\"",
	"COLON_COMMENT",
	"\"secondary\"",
	"\"setroute\"",
	"\"extended\"",
	"\"standard\"",
	"Whitespace",
	"HEX_CONST",
	"NEG_INT_CONST",
	"DIGIT",
	"HEXDIGIT",
	"PIPE_CHAR",
	"NUMBER_SIGN",
	"PERCENT",
	"AMPERSAND",
	"APOSTROPHE",
	"OPENING_PAREN",
	"CLOSING_PAREN",
	"STAR",
	"PLUS",
	"COMMA",
	"MINUS",
	"DOT",
	"SLASH",
	"COLON",
	"SEMICOLON",
	"LESS_THAN",
	"EQUALS",
	"GREATER_THAN",
	"QUESTION",
	"COMMERCIAL_AT",
	"OPENING_SQUARE",
	"CLOSING_SQUARE",
	"CARET",
	"UNDERLINE",
	"OPENING_BRACE",
	"CLOSING_BRACE",
	"TILDE",
	"EXLAMATION",
	0
};

const unsigned long PIXCfgParser::_tokenSet_0_data_[] = { 2UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// EOF 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_0(_tokenSet_0_data_,6);
const unsigned long PIXCfgParser::_tokenSet_1_data_[] = { 134224754UL, 87819264UL, 896UL, 6UL, 0UL, 0UL, 0UL, 0UL };
// EOF NEWLINE "quit" "ip" "names" "name" WORD IPV6 "object" "object-group" 
// "crypto" "certificate" "PIX" "ASA" "hostname" "access-list" "controller" 
// "interface" LINE_COMMENT "exit" COLON_COMMENT 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_1(_tokenSet_1_data_,8);
const unsigned long PIXCfgParser::_tokenSet_2_data_[] = { 1094844480UL, 0UL, 603978752UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "ip" "igmp" "ospf" "pim" "description" "vlan" "speed" "duplex" "ddns" 
// "forward" "delay" "hold-time" "ipv6" "mac-address" "multicast" PPPOE 
// "rip" "no" "security-level" "nameif" "shutdown" "switchport" 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_2(_tokenSet_2_data_,8);
const unsigned long PIXCfgParser::_tokenSet_3_data_[] = { 2281709426UL, 87819264UL, 898UL, 6UL, 0UL, 0UL, 0UL, 0UL };
// EOF NEWLINE "quit" "ip" "names" "name" IPV4 WORD IPV6 "object" "host" 
// "object-group" "crypto" "certificate" "PIX" "ASA" "hostname" "access-list" 
// "any" "controller" "interface" LINE_COMMENT "exit" COLON_COMMENT 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_3(_tokenSet_3_data_,8);
const unsigned long PIXCfgParser::_tokenSet_4_data_[] = { 134209600UL, 16UL, 0UL, 0UL, 0UL, 0UL };
// "ip" "ah" "eigrp" "esp" "gre" "igmp" "igrp" "ipinip" IPSEC "nos" "ospf" 
// "pcp" "pim" PPTP "snp" INT_CONST 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_4(_tokenSet_4_data_,6);
const unsigned long PIXCfgParser::_tokenSet_5_data_[] = { 134224754UL, 3845916161UL, 897UL, 6UL, 0UL, 0UL, 0UL, 0UL };
// EOF NEWLINE "quit" "ip" "names" "name" WORD IPV6 "object" "range" "destination" 
// "object-group" "crypto" "certificate" "PIX" "ASA" "hostname" "access-list" 
// "eq" "gt" "lt" "neq" "controller" "interface" LINE_COMMENT "exit" COLON_COMMENT 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_5(_tokenSet_5_data_,8);
const unsigned long PIXCfgParser::_tokenSet_6_data_[] = { 2281709426UL, 3845916161UL, 1023UL, 6UL, 0UL, 0UL, 0UL, 0UL };
// EOF NEWLINE "quit" "ip" "names" "name" IPV4 WORD IPV6 "object" "host" 
// "range" "destination" "object-group" "crypto" "certificate" "PIX" "ASA" 
// "hostname" "access-list" "eq" "gt" "lt" "neq" "any" "log" "log-input" 
// "established" "fragments" "time-range" "controller" "interface" LINE_COMMENT 
// "exit" COLON_COMMENT 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_6(_tokenSet_6_data_,8);
const unsigned long PIXCfgParser::_tokenSet_7_data_[] = { 16UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// NEWLINE 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_7(_tokenSet_7_data_,6);
const unsigned long PIXCfgParser::_tokenSet_8_data_[] = { 2147484672UL, 0UL, 2UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// IPV4 "host" "any" 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_8(_tokenSet_8_data_,8);
const unsigned long PIXCfgParser::_tokenSet_9_data_[] = { 2147486736UL, 3758096401UL, 127UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// NEWLINE IPV4 WORD "host" "range" INT_CONST "eq" "gt" "lt" "neq" "any" 
// "log" "log-input" "established" "fragments" "time-range" 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_9(_tokenSet_9_data_,8);
const unsigned long PIXCfgParser::_tokenSet_10_data_[] = { 16UL, 0UL, 44UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// NEWLINE "log" "log-input" "fragments" 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_10(_tokenSet_10_data_,8);
const unsigned long PIXCfgParser::_tokenSet_11_data_[] = { 16UL, 0UL, 12UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// NEWLINE "log" "log-input" 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_11(_tokenSet_11_data_,8);
const unsigned long PIXCfgParser::_tokenSet_12_data_[] = { 16UL, 0UL, 108UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// NEWLINE "log" "log-input" "fragments" "time-range" 
const ANTLR_USE_NAMESPACE(antlr)BitSet PIXCfgParser::_tokenSet_12(_tokenSet_12_data_,8);


