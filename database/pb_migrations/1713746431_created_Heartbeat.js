/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "kle4kl5wsp1bdx3",
    "created": "2024-04-22 00:40:31.938Z",
    "updated": "2024-04-22 00:40:31.938Z",
    "name": "Heartbeat",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "ds8wtg9x",
        "name": "message",
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
  const collection = dao.findCollectionByNameOrId("kle4kl5wsp1bdx3");

  return dao.deleteCollection(collection);
})
