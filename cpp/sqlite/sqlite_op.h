#pragma once
#include <string_view>
#include <string>
#include <sqlite3.h>

class SqliteStmt
{
public:
    SqliteStmt();
private:
    sqlite3_stmt *_stmt_ptr;
};

class SqliteConnection
{
public:
    SqliteConnection(const std::string& filename);
    SqliteConnection(std::string&& filename);
    SqliteStmt query(const std::string &sql);
    ~SqliteConnection();
private:
    sqlite3 *_db_ptr; 
    std::string _filename;
};


#include <boost/exception/all.hpp>
using namespace std;

#define THROW_SQLITE_EXCEPTION(x) \
    BOOST_THROW_EXCEPTION(x)

#define THROW_SQLITE_EXCEPTION_IF(cond, x) \
    if (cond) { \
        BOOST_THROW_EXCEPTION(x); \
    }

SqliteConnection::SqliteConnection(string &&filename)
    : _db_ptr{nullptr}
    , _filename(move(filename))
{
    int rc = sqlite3_open(_filename.c_str(), &_db_ptr);
    THROW_SQLITE_EXCEPTION_IF(rc != SQLITE_OK, sqlite3_errmsg(_db_ptr));
}

SqliteConnection::~SqliteConnection()
{
    int rc = sqlite3_close(_db_ptr);
    THROW_SQLITE_EXCEPTION_IF(rc != SQLITE_OK, sqlite3_errmsg(_db_ptr));
}
