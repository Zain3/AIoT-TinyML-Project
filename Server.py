import socket
import pickle
import cv2 
import struct

HOST = "192.168.7.1"  # Standard loopback interface address (localhost)
PORT = 65433  # Port to listen on (non-privileged ports are > 1023)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.settimeout(15.0)
s.bind((HOST, PORT))
s.listen(5)
print("LISTENING AT:",s)

while(True): 
    conn, addr = s.accept()
    print("Client found at {addr}, starting camera...\n")

    if conn:
        
        vid = cv2.VideoCapture(0)
        frame_count = 0
        while(vid.isOpened()):
            ret, frame = vid.read()

            if (frame_count % 12 == 0):
                gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                print(gray_frame.shape)
                gray_frame = cv2.resize(frame, (0, 0), fx = 0.2, fy = 0.2)
                a = pickle.dumps(gray_frame)
                mes = struct.pack("Q",len(a))+a
                print(len(a))
                conn.sendall(mes)

            frame_count = frame_count + 1

            cv2.imshow('frame', frame) 
            key = cv2.waitKey(1) & 0xFF
            if key == ord('q'):
                s.close()
