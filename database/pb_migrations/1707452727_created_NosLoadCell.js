/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "4pl56q5b1xd3w3z",
    "created": "2024-02-09 04:25:27.524Z",
    "updated": "2024-02-09 04:25:27.524Z",
    "name": "NosLoadCell",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "lqmpd83y",
        "name": "nos1_mass",
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
        "id": "f8w93hcd",
        "name": "nos2_mass",
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
  const collection = dao.findCollectionByNameOrId("4pl56q5b1xd3w3z");

  return dao.deleteCollection(collection);
})
