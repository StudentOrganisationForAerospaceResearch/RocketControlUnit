/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "z9evmipyehivigc",
    "created": "2024-02-19 18:03:55.846Z",
    "updated": "2024-02-19 18:03:55.846Z",
    "name": "SystemState",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "rdypdbqf",
        "name": "sys_state",
        "type": "text",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {
          "min": null,
          "max": null,
          "pattern": ""
        }
      },
      {
        "system": false,
        "id": "jo7uaff6",
        "name": "rocket_state",
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
  const collection = dao.findCollectionByNameOrId("z9evmipyehivigc");

  return dao.deleteCollection(collection);
})
