#include "telegram_p.h"

TelegramPrivate* luaState;

extern "C" {

#include "lua-tg.h"


void lua_init()
{

}

void lua_init_file(const char *file)
{
    Q_UNUSED(file);
}

void lua_new_msg(struct message *M)
{

}

void lua_our_id(int id)
{

}

void lua_secret_chat_created(struct secret_chat *U)
{
}

void lua_user_update(struct user *U)
{

}

void lua_chat_update(struct chat *C)
{

}

void lua_binlog_end(void)
{

}

void lua_diff_end(void)
{

}

void lua_do_all(void)
{

}

void lua_username_requested(char** user)
{
    luaState->onUsernameRequested(nullptr);
}

void lua_code_requested(char** code)
{

}

void lua_registration_requested(char** code, char** first_name,
                                char** last_name)
{

}

}
