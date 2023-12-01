import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
from std_msgs.msg import String
import cv2
import numpy as np
from message_filters import Subscriber
from ultralytics import YOLO
from geometry_msgs.msg import Twist
import time

class vision_perception(Node):
    def __init__(self):
        super().__init__("vision_perception")
        self.image_subscriber = self.create_subscription(
            CompressedImage, "/unity_camera/rgb/image_raw/compressed", self.perception_callback, 10)
        self.image_subscriber
        self.found_target = {}
        # 读取模型
        self.model = YOLO(
            "tutorial/tutorial/ros2_ws/src/yolo_demo/model/yolov8s.pt")

    
    def perception_callback(self, image_msg):
        """-------------图像处理--------------------"""
        try:
            # 将压缩图像数据解码为OpenCV图像对象
            np_arr = np.frombuffer(image_msg.data, np.uint8)
            # image是BGR的，而imshow接收的也是BGR的
            image = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
            results = self.model.predict(
                source=image, save=False, verbose=True, save_txt=False, show=True)
            self.class_dict = results[0].names
            bounding_boxes = results[0].boxes.data.cpu()
            conf = results[0].boxes.conf
        except cv2.error as e:
            print('Failed to decode image:'+str(e))
        try:
            counter =0
            for bounding_box in bounding_boxes:  # xyxy的格式
                # https://docs.ultralytics.com/reference/engine/results/#ultralytics.engine.results.Boxes
                target_name = self.class_dict[int(bounding_box[5])]  # 目标名称
                if  conf[counter] > 0.3:
                    if self.found_target.get(target_name,None) == None:
                        self.found_target[target_name] = 1
                    else:
                        self.found_target[target_name] += 1
                        self.target_x1 = bounding_box[0]  # 左目标点
                        self.target_x2 = bounding_box[2]  # 右目标点
                    if self.found_target[target_name]%15 == 0:
                        self.get_logger().info("Find Target {}".format(target_name))
                        self.found_target[target_name] = 0
                counter += 1
        except IndexError:
            self.get_logger().warn("didn't detect target")
            return


def main(args=None):
    rclpy.init(args=args)
    # 创建ROS节点
    node_ = vision_perception()
    node_.get_logger().info("perception创建成功")
    try:
        rclpy.spin(node_)
    finally:
        node_.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()