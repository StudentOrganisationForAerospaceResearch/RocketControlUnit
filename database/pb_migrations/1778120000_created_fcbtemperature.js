/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "fcbtempnew00001",
    "created": "2026-05-08 00:00:00.000Z",
    "updated": "2026-05-08 00:00:00.000Z",
    "name": "fcbtemperature",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "upvtc001",
        "name": "upper_pv_tc",
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
        "id": "venttc01",
        "name": "vent_solenoid_tc",
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
        "id": "diptc001",
        "name": "dip_tube_tc",
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
  const collection = dao.findCollectionByNameOrId("fcbtempnew00001");

  return dao.deleteCollection(collection);
})
