/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "kklpl8z6cciwv9v",
    "created": "2024-02-09 04:25:27.523Z",
    "updated": "2024-02-09 04:25:27.523Z",
    "name": "PbbPressure",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "q1t4yz2t",
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
      },
      {
        "system": false,
        "id": "ibeo913g",
        "name": "lower_pv_pressure",
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
  const collection = dao.findCollectionByNameOrId("kklpl8z6cciwv9v");

  return dao.deleteCollection(collection);
})
