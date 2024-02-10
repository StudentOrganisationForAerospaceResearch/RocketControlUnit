/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "echs4r07dfwjnq0",
    "created": "2024-02-09 04:25:27.524Z",
    "updated": "2024-02-09 04:25:27.524Z",
    "name": "SobTemp",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "wxjvwy1a",
        "name": "tc1_temp",
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
        "id": "s1niph28",
        "name": "tc2_temp",
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
  const collection = dao.findCollectionByNameOrId("echs4r07dfwjnq0");

  return dao.deleteCollection(collection);
})
