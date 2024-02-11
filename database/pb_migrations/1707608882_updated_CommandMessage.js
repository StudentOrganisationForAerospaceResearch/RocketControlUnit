/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("s3u9kc1izqjaeds")

  // add
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "mnnfsbob",
    "name": "source_sequence_num",
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
  const collection = dao.findCollectionByNameOrId("s3u9kc1izqjaeds")

  // remove
  collection.schema.removeField("mnnfsbob")

  return dao.saveCollection(collection)
})
