/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("11ezzv9sbk3qspa")

  // remove
  collection.schema.removeField("3kn4zlbe")

  // add
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "qmsssqlp",
    "name": "power_source",
    "type": "text",
    "required": false,
    "presentable": false,
    "unique": false,
    "options": {
      "min": null,
      "max": null,
      "pattern": ""
    }
  }))

  return dao.saveCollection(collection)
}, (db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("11ezzv9sbk3qspa")

  // add
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "3kn4zlbe",
    "name": "power_source",
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

  // remove
  collection.schema.removeField("qmsssqlp")

  return dao.saveCollection(collection)
})
