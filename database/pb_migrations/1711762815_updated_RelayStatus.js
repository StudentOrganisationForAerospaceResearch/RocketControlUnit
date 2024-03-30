/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("3wqika2hahhv173")

  // update
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "vwso5m6b",
    "name": "pbv3_open",
    "type": "bool",
    "required": false,
    "presentable": false,
    "unique": false,
    "options": {}
  }))

  return dao.saveCollection(collection)
}, (db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("3wqika2hahhv173")

  // update
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "vwso5m6b",
    "name": "pbv3_oepn",
    "type": "bool",
    "required": false,
    "presentable": false,
    "unique": false,
    "options": {}
  }))

  return dao.saveCollection(collection)
})
