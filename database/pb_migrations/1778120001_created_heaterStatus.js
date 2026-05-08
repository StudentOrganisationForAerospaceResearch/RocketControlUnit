/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "heaterstat00001",
    "created": "2026-05-08 00:00:00.000Z",
    "updated": "2026-05-08 00:00:00.000Z",
    "name": "heaterStatus",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "uphtr001",
        "name": "upper_pv_heater_on",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "lowhtr01",
        "name": "lower_pv_heater_on",
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
  const collection = dao.findCollectionByNameOrId("heaterstat00001");

  return dao.deleteCollection(collection);
})
