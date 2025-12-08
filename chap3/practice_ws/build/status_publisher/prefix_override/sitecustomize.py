import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/media/witcher/be8e6b9d-6c5f-43b6-8399-13e2698fc3d1/chap3/practice_ws/install/status_publisher'
