/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "pcaf3wac1tq24ym",
    "created": "2024-04-26 16:43:29.477Z",
    "updated": "2024-04-26 16:43:29.477Z",
    "name": "LoadCellCalibrationCurves",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "xlik8f63",
        "name": "name",
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
        "id": "fd2bg9po",
        "name": "slope",
        "type": "json",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {
          "maxSize": 2000000
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
  const collection = dao.findCollectionByNameOrId("pcaf3wac1tq24ym");

  return dao.deleteCollection(collection);
})
