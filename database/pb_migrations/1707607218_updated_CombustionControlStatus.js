/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("iem7zt60sts5imk")

  // update
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "hjwapp3k",
    "name": "mev_open",
    "type": "bool",
    "required": false,
    "presentable": false,
    "unique": false,
    "options": {}
  }))

  return dao.saveCollection(collection)
}, (db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("iem7zt60sts5imk")

  // update
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "hjwapp3k",
    "name": "mev_power_enable",
    "type": "bool",
    "required": false,
    "presentable": false,
    "unique": false,
    "options": {}
  }))

  return dao.saveCollection(collection)
})
