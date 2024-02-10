/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "5lnm8njyxd45lc8",
    "created": "2024-02-09 04:25:27.524Z",
    "updated": "2024-02-09 04:25:27.524Z",
    "name": "MevState",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "d1vid24j",
        "name": "mev_open",
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
  const collection = dao.findCollectionByNameOrId("5lnm8njyxd45lc8");

  return dao.deleteCollection(collection);
})
