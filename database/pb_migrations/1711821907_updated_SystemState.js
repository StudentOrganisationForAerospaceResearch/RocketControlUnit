/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("z9evmipyehivigc")

  collection.name = "sys_state"

  return dao.saveCollection(collection)
}, (db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("z9evmipyehivigc")

  collection.name = "SystemState"

  return dao.saveCollection(collection)
})
