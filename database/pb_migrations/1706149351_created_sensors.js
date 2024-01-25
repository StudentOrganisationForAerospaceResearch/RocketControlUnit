/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "n7nf208brxotq23",
    "created": "2024-01-25 02:22:31.467Z",
    "updated": "2024-01-25 02:22:31.467Z",
    "name": "sensors",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "qijk9sry",
        "name": "tc1",
        "type": "text",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {
          "min": null,
          "max": null,
          "pattern": ""
        }
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
  const collection = dao.findCollectionByNameOrId("n7nf208brxotq23");

  return dao.deleteCollection(collection);
})
