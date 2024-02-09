import message_pb2

def encode_message(name, id):
    # Create a new Test message
    test_message = message_pb2.Test()

    # Set the fields
    test_message.name = name
    test_message.id = id

    # Encode the message to a byte string
    encoded_message = test_message.SerializeToString()

    return encoded_message

def decode_message(encoded_message):
    # Create a new Test message
    test_message = message_pb2.Test()
    # Decode the byte string to the Test message
    test_message.ParseFromString(encoded_message)

    return test_message

# Test the encode_message and decode_message functions
encoded_message = encode_message('Alice', 123)
print('Encoded message:', encoded_message)

decoded_message = decode_message(encoded_message)
print('Decoded message:', 'name:', decoded_message.name, 'id:', decoded_message.id)