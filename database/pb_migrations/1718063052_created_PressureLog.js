/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "1nba8h2zxy3ivx5",
    "created": "2024-06-10 23:44:12.627Z",
    "updated": "2024-06-10 23:44:12.627Z",
    "name": "PressureLog",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "iy7ghgcf",
        "name": "time",
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
        "id": "4kgw6ak3",
        "name": "pv_pressure",
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
        "id": "bbwpu0x2",
        "name": "ib_pressure",
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
    "createRule": null,
    "updateRule": null,
    "deleteRule": null,
    "options": {}
  });

  return Dao(db).saveCollection(collection);
}, (db) => {
  const dao = new Dao(db);
  const collection = dao.findCollectionByNameOrId("1nba8h2zxy3ivx5");

  return dao.deleteCollection(collection);
})
