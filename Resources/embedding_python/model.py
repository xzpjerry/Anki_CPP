import pymongo
from pymongo import MongoClient
from pymongo import IndexModel, ASCENDING, DESCENDING
import sys
import logging

class DB_config(object):

    def __init__(self, user, userpw, dbhost, dbport, dbname):
        self.url = u"mongodb://%s:%s@%s:%s/%s" % (
            user, userpw, dbhost, dbport, dbname)
        self.user = user
        self.userpw = userpw
        self.dbhost = dbhost
        self.dbport = dbport
        self.dbname = dbname

    def __str__(self):
        return self.url


# class record(object):

#     def __init__(self, date, front, back): # Inputed date will always be in unix timestamp format
#         self.date = date
#         self.front = front
#         self.back = back

#     def formatted(self):
#         temp = {
#                 u"date": self.date,
#                 u"front": self.front,
#                 u"back": self.back
#                 }
#         return temp

#     def __str__(self):
#         return unicode(self.formatted())


# class DB(object):

#     def __init__(self, config):
#         try:
#             self.db = getattr(MongoClient(config.url), config.dbname)
#             self.collection = None
#             logging.info(u"Collection is not yet set for now.")
#         except:
#             logging.warning(
#                 u"Can not connect to the Database, please check your config.")
#             sys.exit(1)

#     def set_collection(self, collection):
#         try:
#             self.collection = getattr(self.db, collection)
#             index = IndexModel([(u"date", DESCENDING)])
#             self.collection.create_indexes([index])
#         except:
#             logging.warning(
#                 u"Can not connect to the collection or the collection is not existed? Do you have permission to write?.")
#             raise
#         finally:
#             logging.info(u"Now the collection is set.")
#             for index in self.collection.list_indexes():
#                 logging.info(u"Using index: " + unicode(index))

#     def del_collection(self):
#         if self.collection != None:
#             try:
#                 self.collection.drop()
#             except Exception, e:
#                 logging.warning(u"Deletion failed.")
#                 raise
#             finally:
#                 logging.info(u"DB deleted.")

#     def delete_memos(self, date, front, back):
#         if self.collection != None:
#             try:
#                 self.collection.delete_many(record(date, front, back).formatted())
#             except:
#                 logging.warning(
#                     u"Can not connect to the collection, is the collection exist? Do you have permission to write?.")
#                 raise
#             finally:
#                 logging.info(u"All related records deleted.")
#         else:
#             logging.warning(u"Collection is not yet set.")
#             logging.warning(u"Nothing to delete.")

#     def insert(self, date, front, back):
#         if self.collection != None:
#             try:
#                 logging.info(u"Inserting ")
#                 self.collection.insert(record(date, front, back).formatted())
#             except:
#                 logging.warning(
#                     u"Can not connect to the collection, is the collection exist? Do you have permission to write?.")
#                 logging.warning(u"Insertion failed.")
#                 raise
#             finally:
#                 logging.info(u"Record inserted.")
#         else:
#             logging.warning(u"Collection is not yet set.")
#             logging.warning(u"Insertion failed.")

#     def get(self, record, title):
#         try:
#             print record
#             result = self.collection.find_one(record)
#             del result[u'_id']
#             return result
#         except:
#             logging.warning(
#                 u"Can not connect to the collection, is the collection exist? Do you have permission to write?.")
#             logging.warning(u"Fetch failed.")
#             raise
#         finally:
#             logging.info(u"Found and returned!")

#     def get_all(self):
#         if self.collection != None:
#             try:
#                 records = []
#                 for onerecord in self.collection.find().sort([(u"date", DESCENDING)]):
#                     del onerecord[u'_id']
#                     records.append(onerecord)
#             except:
#                 logging.warning(
#                     u"Can not connect to the collection, is the collection exist? Do you have permission to write?.")
#                 logging.warning(u"Fetch failed.")
#                 raise
#             finally:
#                 return records
#         else:
#             logging.warning(u"Collection is not yet set.")
#             logging.warning(u"Finding failed.")
