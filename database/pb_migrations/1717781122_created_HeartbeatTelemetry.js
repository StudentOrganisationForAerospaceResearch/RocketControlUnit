/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const collection = new Collection({
    "id": "yk2fowsgnb3259n",
    "created": "2024-06-07 17:25:22.246Z",
    "updated": "2024-06-07 17:25:22.246Z",
    "name": "HeartbeatTelemetry",
    "type": "base",
    "system": false,
    "schema": [
      {
        "system": false,
        "id": "zqxmlzl7",
        "name": "timer_state",
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
        "id": "ghtrhwih",
        "name": "timer_period",
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
        "id": "4wfgogja",
        "name": "timer_remaining",
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
  const collection = dao.findCollectionByNameOrId("yk2fowsgnb3259n");

  return dao.deleteCollection(collection);
})
