import socket
import cv2
import pickle
import struct
import serial
import socket

from struct import *

# face_detect
# Detects faces, returns bounding box dimensions
# Param 'frame': video or image frame
# Param 'faceCascade': path to cascade xml file
# Returns object array containing (x,y,w,h) of bounding boxes.
def face_detect(frame, faceCascade):
    """
        Inputs: frame (numpy array) and faceCascade XML model
        Output: faces (https://docs.opencv.org/3.4/db/d28/tutorial_cascade_classifier.html)
    """
    if len(frame.shape)==3:
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    else:
        gray = frame

    # Detect faces in an frame
    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=2,
        minSize=(10, 10)
    )
    return faces

# draw_face_boxes
# Draws bounding boxes on image
# Param 'frame': video or image frame
# Param 'faces': faces object array containing (x,y,w,h) of bounding boxes.
# Returns image with bounding box overlay
def draw_face_boxes(frame, faces):
    # draw bounding boxes for all faces in frame
    if faces is None:
        return frame
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
    return frame


if __name__=="__main__":
    HOST = "192.168.7.1"  # The server's hostname or IP address
    PORT = 65433  # The port used by the server

    cascPath = "haarcascade_frontalface_default.xml"

    # UART port
    ser = serial.Serial(
        port='/dev/ttyS4', 
        baudrate=115200, 
        timeout=1,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS
    )

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print("Socket created, connecting to server:\n")
    s.connect((HOST, PORT))
    print("Connected!")

    data = b""
    payload_size = struct.calcsize("Q")
    print(payload_size)

    while True:
        while (len(data) < payload_size):
            packet = s.recv(8*1024) # 4K
            print("Data received\n")
            if not packet: break
            data+=packet

        packed_msg_size = data[:payload_size]
        data = data[payload_size:]
        msg_size = struct.unpack("Q",packed_msg_size)[0]

        while len(data) < msg_size:
            data += s.recv(8*1024)

        frame_data = data[:msg_size]
        data  = data[msg_size:]
        frame = pickle.loads(frame_data)
        key = cv2.waitKey(1) & 0xFF

        if key == ord('q'):
            s.close()

        if (len(frame) != 0):
            # Create the haar cascade
            faceCascade = cv2.CascadeClassifier(cascPath)
            faces = face_detect(frame, faceCascade)
            print("Found {0} faces!".format(len(faces)))

            for (x, y, w, h) in faces:
                msg = pack("<c6Hc", 'I'.encode(),x, y, w, h, frame.shape[0], frame.shape[1], 'i'.encode())
                ser.write(msg)
            
        else:
            print ("No frame!")
