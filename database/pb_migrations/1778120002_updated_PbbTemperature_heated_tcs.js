/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("ulgz8r24y28mj14")

  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "lpvtc001",
    "name": "lower_pv_tc1",
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

  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "lshtc001",
    "name": "low_solenoid_heater_tc",
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
  const collection = dao.findCollectionByNameOrId("ulgz8r24y28mj14")

  collection.schema.removeField("lpvtc001")
  collection.schema.removeField("lshtc001")

  return dao.saveCollection(collection)
})
