/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("pcaf3wac1tq24ym")

  // remove
  collection.schema.removeField("fd2bg9po")

  // add
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "0scqimpj",
    "name": "slope",
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

  // add
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "fd2bg9po",
    "name": "slope",
    "type": "json",
    "required": false,
    "presentable": false,
    "unique": false,
    "options": {
      "maxSize": 2000000
    }
  }))

  // remove
  collection.schema.removeField("0scqimpj")

  return dao.saveCollection(collection)
})
