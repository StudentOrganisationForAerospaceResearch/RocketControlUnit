/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "5hlbgj06sbpat4p",
    "created": "2024-10-21 16:41:45.318Z",
    "updated": "2024-10-21 16:41:45.318Z",
    "name": "BoardStatus",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "eo31ezna",
        "name": "dmb_status",
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
        "id": "j2fhjq9v",
        "name": "pmb_status",
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
    "listRule": null,
    "viewRule": null,
    "createRule": null,
    "updateRule": null,
    "deleteRule": null,
    "options": {}
  });

  return Dao(db).saveCollection(collection);
}, (db) => {
  const dao = new Dao(db);
  const collection = dao.findCollectionByNameOrId("5hlbgj06sbpat4p");

  return dao.deleteCollection(collection);
})
