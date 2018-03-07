/* Please check out https://mongodb.github.io/mongo-cxx-driver/mongocxx-v3/installation/
 * to get start.
 * To compile, use:
 * g++ --std=c++11 mongoDB_test.cpp -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 \
  -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 \
  -L/usr/local/lib -lmongocxx -lbsoncxx
 * assuming you have installed mogoDB driver to /usr/local/lib
 */
#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>


int main(int, char**) {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{"mongodb://bot:53744D9E-0C0B-4298-851A-AEB56ECE58F7@ds139984.mlab.com:39984/cis330"}};
    mongocxx::database db = conn["cis330"];

    auto collection = db["test"];
    // insert a record
    auto hello_world = bsoncxx::builder::stream::document{} << "hello" << "world" << bsoncxx::builder::stream::finalize;
    collection.insert_one(hello_world.view());
    /*
            {
           "name" : "MongoDB",
           "type" : "database",
           "count" : 1,
           "versions": [ "v3.2", "v3.0", "v2.6" ],
           "info" : {
                       "x" : 203,
                       "y" : 102
                    }
        }
    */
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
        << "name" << "mongodb"
        << "type" << "database"
        << "version" << bsoncxx::builder::stream::open_array
            << "V3.2" << "V3.0" << "V2.6"
        << bsoncxx::builder::stream::close_array
        << "info" << bsoncxx::builder::stream::open_document
            << "x" << 203
            << "Y" << 102
        << bsoncxx::builder::stream::close_document
        << "modified times" << 0
        << "created@" << (long long)time(0) // be careful to the timestamp
        <<bsoncxx::builder::stream::finalize;

    collection.insert_one(doc_value.view());

    // find all the record satisfied filters (every record named mongodb)
    std::cout << "Finding records named \"mongodb\"\n";
    auto cursor = collection.find(bsoncxx::builder::stream::document{} << "name" << "mongodb" << bsoncxx::builder::stream::finalize);

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    std::cout << "Query done\n\n";

    // find all the record sorted in descendence order of their created times;
    auto order = bsoncxx::builder::stream::document{} << "created@" << -1 << bsoncxx::builder::stream::finalize;
    std::cout << "Finding every record\n";
    auto opts = mongocxx::options::find{};
    opts.sort(order.view());
    auto cursor2 = collection.find({}, opts);

    for (auto&& doc : cursor2) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    std::cout << "QUery done\n\n";

    // update/modify records satisfied filters (every record named mongodb)
    bsoncxx::stdx::optional<mongocxx::result::update> result = collection.update_many(
            bsoncxx::builder::stream::document{} << "name" << "mongodb" << bsoncxx::builder::stream::finalize,
            bsoncxx::builder::stream::document{} << "$inc" << bsoncxx::builder::stream::open_document << "modified times" << 1 << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize  
        );

    // delete records satisfied filters(records have been modified 5 times)
    bsoncxx::stdx::optional<mongocxx::result::delete_result> result2 = collection.delete_many(
            bsoncxx::builder::stream::document{} << "modified times" << bsoncxx::builder::stream::open_document <<
                "$gt" << 5 << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize
        );

    if(result2) {std::cout << "Deleted " << result2 -> deleted_count() << "records.\n";}
}