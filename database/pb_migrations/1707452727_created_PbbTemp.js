/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "ulgz8r24y28mj14",
    "created": "2024-02-09 04:25:27.523Z",
    "updated": "2024-02-09 04:25:27.523Z",
    "name": "PbbTemp",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "q2r1kzhv",
        "name": "ib_temperature",
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
        "id": "rikipdpv",
        "name": "pv_temperature",
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
  const collection = dao.findCollectionByNameOrId("ulgz8r24y28mj14");

  return dao.deleteCollection(collection);
})
