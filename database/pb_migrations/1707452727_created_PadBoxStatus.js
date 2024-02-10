/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "6rulnfo36iqwnbq",
    "created": "2024-02-09 04:25:27.524Z",
    "updated": "2024-02-09 04:25:27.524Z",
    "name": "PadBoxStatus",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "eqprffop",
        "name": "cont1",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "izkhxknd",
        "name": "cont2",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "kcfyon3k",
        "name": "box1_on",
        "type": "bool",
        "required": false,
        "presentable": false,
        "unique": false,
        "options": {}
      },
      {
        "system": false,
        "id": "exkdbj8l",
        "name": "box2_on",
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
  const collection = dao.findCollectionByNameOrId("6rulnfo36iqwnbq");

  return dao.deleteCollection(collection);
})
