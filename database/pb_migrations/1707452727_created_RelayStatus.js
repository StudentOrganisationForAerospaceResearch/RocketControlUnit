/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "3wqika2hahhv173",
    "created": "2024-02-09 04:25:27.524Z",
    "updated": "2024-02-09 04:25:27.524Z",
    "name": "RelayStatus",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "hqqnioxz",
        "name": "ac1_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "sh0m5ljt",
        "name": "ac2_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "8my1mqm5",
        "name": "pbv1_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "hqtqxvhb",
        "name": "pbv2_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "vwso5m6b",
        "name": "pbv3_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "vhbcr8kt",
        "name": "sol1_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "fhpjobam",
        "name": "sol2_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "hxd2jnzs",
        "name": "sol3_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "2v4n1hfu",
        "name": "sol4_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "1hmajmbp",
        "name": "sol5_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "deexnzap",
        "name": "sol6_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "n4swwkp7",
        "name": "sol7_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "smoke1zg",
        "name": "sol8a_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "doh75wrd",
        "name": "sol8b_open",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      }
    ],
    "indexes": [],
    "listRule": "",
    "viewRule": "",
    "createRule": "",
    "updateRule": "",
    "deleteRule": "",
    "options": {}
  });

  return Dao(db).saveCollection(collection);
}, (db) => {
  const dao = new Dao(db);
  const collection = dao.findCollectionByNameOrId("3wqika2hahhv173");

  return dao.deleteCollection(collection);
})
