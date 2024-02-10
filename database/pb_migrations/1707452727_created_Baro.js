/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "2j2bfgv8i8le9vo",
    "created": "2024-02-09 04:25:27.523Z",
    "updated": "2024-02-09 04:25:27.523Z",
    "name": "Baro",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "qyfkv2io",
        "name": "baro_pressure",
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
        "id": "pq0htqa7",
        "name": "baro_temp",
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
  const collection = dao.findCollectionByNameOrId("2j2bfgv8i8le9vo");

  return dao.deleteCollection(collection);
})
