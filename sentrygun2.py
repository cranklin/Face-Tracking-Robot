import cv
import serial

def detectFace(image):
    storage = cv.CreateMemStorage()
    haar=cv.Load('/opt/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml')
    detected = cv.HaarDetectObjects(image, haar, storage, 1.2, 2,cv.CV_HAAR_DO_CANNY_PRUNING, (100,100))
    if detected:
        for face in detected:
            return face
    else:
        return False

def templateMatchFace(image,template,result):
    cv.MatchTemplate(image,template,result,cv.CV_TM_SQDIFF)
    (min_x,max_y,minloc,maxloc)=cv.MinMaxLoc(result)
    return minloc

def moveSentry(targetx,targety):
    # x,y coordinates.
    ser.write(str(targetx)+"x"+str(targety)+"y")

def directSentry(direction): 
    # 0: reset 1-4: N-W
    ser.write(str(direction))

if __name__ == '__main__':
    # activate camera
    cv.NamedWindow('tempwindow',cv.CV_WINDOW_AUTOSIZE)
    capture = cv.CaptureFromCAM(0)
    image = cv.QueryFrame(capture)
    W,H = cv.GetSize(image)
    #calculate center of image
    centerScreenX = cv.Round(W/2)
    centerScreenY = cv.Round(H/2)
    
    # initialize serial port
    ser = serial.Serial(port='/dev/tty.usbmodemfd111',baudrate=19200,timeout=0)
    directSentry(0)
    #moveSentry(90,90)

    while True:
        image = cv.QueryFrame(capture)
        face = detectFace(image)
        if face:
            ((hx,hy,hw,hh),hn) = face
            cv.SetImageROI(image, (int(hx),int(hy),hw,hh))
            template = cv.CloneImage(image)
            cv.ResetImageROI(image)
            w,h = cv.GetSize(template)
            width = W-w+1
            height = H-h+1
            result = cv.CreateImage((width,height),32,1)
            #calculate center
            centerX = int(hx)+cv.Round(hw/2)
            centerY = int(hy)+cv.Round(hh/2)
            if centerX > centerScreenX+200:
                #print centerX-centerScreenX
                directSentry(4)
            elif centerX < centerScreenX-200:
                #print centerScreenX-centerX
                directSentry(2)
            if centerY > centerScreenY+200:
                #print centerY - centerScreenY
                directSentry(1)
            elif centerY < centerScreenY-200:
                #print centerScreenY - centerY
                directSentry(3)
            #white box for face detection
            cv.Rectangle(image,(int(hx),int(hy)),(int(hx)+hw,int(hy)+hh),(255,255,255),3,0)
        cv.ShowImage('tempwindow',image)
        if cv.WaitKey(5) >= 0:
            break
