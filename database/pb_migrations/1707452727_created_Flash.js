/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "xecmpy3hm9h7o2b",
    "created": "2024-02-09 04:25:27.523Z",
    "updated": "2024-02-09 04:25:27.523Z",
    "name": "Flash",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "gzxqzdan",
        "name": "sector_address",
        "type": "number",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {
          "min": null,
          "max": null,
          "noDecimal": false
        }
      },
      {
        "system": false,
        "id": "rulo1pus",
        "name": "logging_rate",
        "type": "number",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {
          "min": null,
          "max": null,
          "noDecimal": false
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
  const collection = dao.findCollectionByNameOrId("xecmpy3hm9h7o2b");

  return dao.deleteCollection(collection);
})
