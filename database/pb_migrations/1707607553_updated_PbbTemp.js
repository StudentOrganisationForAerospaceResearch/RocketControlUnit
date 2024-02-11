/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("ulgz8r24y28mj14")

  collection.name = "PbbTemperature"

  return dao.saveCollection(collection)
}, (db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("ulgz8r24y28mj14")

  collection.name = "PbbTemp"

  return dao.saveCollection(collection)
})
