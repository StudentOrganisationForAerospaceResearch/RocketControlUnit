/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("yk2fowsgnb3259n")

  collection.name = "hb_state"

  return dao.saveCollection(collection)
}, (db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("yk2fowsgnb3259n")

  collection.name = "timer_state"

  return dao.saveCollection(collection)
})
