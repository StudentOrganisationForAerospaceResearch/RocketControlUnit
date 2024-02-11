/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("2j2bfgv8i8le9vo")

  // update
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "pq0htqa7",
    "name": "baro_temperature",
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
  const collection = dao.findCollectionByNameOrId("2j2bfgv8i8le9vo")

  // update
  collection.schema.addField(new SchemaField({
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
  }))

  return dao.saveCollection(collection)
})
