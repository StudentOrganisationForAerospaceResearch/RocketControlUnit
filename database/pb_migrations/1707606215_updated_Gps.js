/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("tf07s5lzkepfmjb")

  // remove
  collection.schema.removeField("k3ee7shb")

  return dao.saveCollection(collection)
}, (db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("tf07s5lzkepfmjb")

  // add
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "k3ee7shb",
    "name": "message_id",
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
