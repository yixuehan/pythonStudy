#include<iostream>
#include <vector>
#include <sqlite_modern_cpp.h>
using namespace  sqlite;
using namespace std;

#include <boost/timer/timer.hpp>

void generate_ids(vector<int> &ids, int count)
{
    ids.reserve(count);
    for (int i = 0; i < count; ++i) {
        ids.push_back(i);
    }
    // random
    for (size_t i = 0; i < (ids.size()-1); ++i) {
        int p = (random() % (ids.size() - i)) + i;
        std::swap(ids[i], ids[p]);
    }
    // for (int i = 0; i < count; ++i) {
    //     cout << ids[i] << ' ';
    // }
    // cout << endl;
}

int main() {
    srand(time(nullptr));
    vector<int> ids;
    generate_ids(ids, 1000000);

   try {
      // creates a database file 'dbfile.db' if it does not exists.
      sqlite_config config;
      config.flags = OpenFlags::READWRITE | OpenFlags::SHAREDCACHE | OpenFlags::CREATE;
      // database db("dbfile.db", config);
      database db("dbfile.db");
      // database db(":memory:");

      // executes the query and creates a 'user' table
      db <<
         "create table if not exists user ("
         "   id integer primary key,"
         "   age int,"
         "   name text,"
         "   weight real"
         ");";

      // db << "pragma cache_size=100000";

      // inserts a new user record.
      // binds the fields to '?' .
      // note that only types allowed for bindings are :
      //      int ,long, long long, float, double
      //      string , u16string
      // sqlite3 only supports utf8 and utf16 strings, you should use std::string for utf8 and std::u16string for utf16.
      // note that u"my text" is a utf16 string literal of type char16_t * .
        {
            boost::timer::auto_cpu_timer t;
            db << "begin;";
            for (size_t i = 0; i < ids.size(); ++i) {
              db << "insert into user (id, age,name,weight) values (?, ?,?,?);"
                 << i
                 << 20
                 << u"bob"
                 << 83.25;
            }
            db << "commit;";
        }

      // int age = 21;
      // float weight = 68.5;
      // string name = "jack";
      // db << "insert into user (id, age,name,weight) values (2, ?,?,?);" // utf16 query string
      //    << age
      //    << name
      //    << weight;

      // cout << "The new record got assigned id " << db.last_insert_rowid() << endl;

      // slects from user table on a condition ( age > 18 ) and executes
      // the lambda for each row returned .
      // int age; string name; double weight;
        {
            int age;
            float weight;
            string name;
            boost::timer::auto_cpu_timer t;
            db << "begin;";
            for (size_t i = 0; i < ids.size(); ++i) {
                db << "select age,name,weight from user where id=?;"
                   << i;
                   // >> tie(age, name, weight);
                  // cout << age << ' ' << name << ' ' << weight << endl;
            }
            db << "commit;";
        }
        {
            int age;
            float weight;
            string name;
            boost::timer::auto_cpu_timer t;
            for (size_t i = 0; i < ids.size(); ++i) {
                db << "select age,name,weight from user where id=?;"
                   << i
                   >> tie(age, name, weight);
                  // cout << age << ' ' << name << ' ' << weight << endl;
            }
        }
         // >> [&](int age, string name, double weight) {
         //    cout << age << ' ' << name << ' ' << weight << endl;
         // };

      // selects the count(*) from user table
      // note that you can extract a single culumn single row result only to : int,long,long,float,double,string,u16string
      // int count = 0;
      // db << "select count(*) from user" >> count;
      // cout << "cout : " << count << endl;

      // // you can also extract multiple column rows
      // db << "select age, name from user where id=1;" >> tie(age, name);
      // cout << "Age = " << age << ", name = " << name << endl;

      // // this also works and the returned value will be automatically converted to string
      // string str_count;
      // db << "select count(*) from user" >> str_count;
      // cout << "scount : " << str_count << endl;
   }
   catch (exception& e) {
      cout << e.what() << endl;
   }
}
