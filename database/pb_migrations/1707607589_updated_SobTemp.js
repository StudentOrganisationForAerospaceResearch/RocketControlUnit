/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("echs4r07dfwjnq0")

  collection.name = "SobTemperature"

  return dao.saveCollection(collection)
}, (db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("echs4r07dfwjnq0")

  collection.name = "SobTemp"

  return dao.saveCollection(collection)
})
