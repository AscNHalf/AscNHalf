/* AscNHalf */

#ifndef __LOGONOPCODES_H
#define __LOGONOPCODES_H

enum RealmListOpcodes
{
	// Initialization of server/client connection...
	RCMSG_REGISTER_REALM						= 1,
	RSMSG_REALM_REGISTERED						= 2,

	// Upon client connect (for WS)
	RCMSG_REQUEST_SESSION						= 3,
	RSMSG_SESSION_RESULT						= 4,

	// Ping/Pong
	RCMSG_PING									= 5,
	RSMSG_PONG									= 6,

	// SQL Query Execute
	RCMSG_SQL_EXECUTE							= 7,
	RCMSG_RELOAD_ACCOUNTS						= 8,

	// Authentication
	RCMSG_AUTH_CHALLENGE						= 9,
	RSMSG_AUTH_RESPONSE							= 10,

	// Character->Account Transmission
	RSMSG_REQUEST_ACCOUNT_CHARACTER_MAPPING		= 11,
	RCMSG_ACCOUNT_CHARACTER_MAPPING_REPLY		= 12,

	// Update Character->Account Mapping
	RCMSG_UPDATE_CHARACTER_MAPPING_COUNT		= 13,
	RSMSG_DISCONNECT_ACCOUNT					= 14,

	// Console auth
	RCMSG_TEST_CONSOLE_LOGIN					= 15,
	RSMSG_CONSOLE_LOGIN_RESULT					= 16,

	// DB modifying
	RCMSG_MODIFY_DATABASE						= 17,

	// S->C ping
	RSMSG_SERVER_PING							= 18,
	RCMSG_SERVER_PONG							= 19,

	// count
	RMSG_COUNT									= 20,
};

#endif
