import rclpy
from rclpy.node import Node

def main():
    rclpy.init()
    node=Node("pynode")
    node.get_logger().info("pynode")
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ =="__main__":
    main()