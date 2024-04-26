/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("pcaf3wac1tq24ym")

  // update
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "582yjc91",
    "name": "intercept",
    "type": "number",
    "required": false,
    "presentable": false,
    "unique": false,
    "options": {
      "min": null,
      "max": null,
      "noDecimal": false
    }
  }))

  return dao.saveCollection(collection)
}, (db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("pcaf3wac1tq24ym")

  // update
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "582yjc91",
    "name": "y_intercept",
    "type": "number",
    "required": false,
    "presentable": false,
    "unique": false,
    "options": {
      "min": null,
      "max": null,
      "noDecimal": false
    }
  }))

  return dao.saveCollection(collection)
})
