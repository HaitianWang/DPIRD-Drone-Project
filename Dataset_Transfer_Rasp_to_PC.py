import paramiko
from scp import SCPClient
import os
import logging

# 配置日志记录
logging.basicConfig(
    filename='transfer_log.txt', 
    level=logging.INFO, 
    format='%(asctime)s - %(levelname)s - %(message)s'
)

def create_ssh_client(hostname, port, username, password):
    """
    创建一个SSH客户端连接到树莓派。
    """
    try:
        client = paramiko.SSHClient()
        client.load_system_host_keys()
        client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        client.connect(hostname, port=port, username=username, password=password)
        logging.info("SSH connection established.")
        return client
    except Exception as e:
        logging.error(f"Failed to connect via SSH: {e}")
        raise

def transfer_files(ssh_client, local_folder, remote_folder):
    """
    使用 SCP 将 Windows 中的文件夹传输到 Raspberry Pi 的指定目录。
    """
    try:
        with SCPClient(ssh_client.get_transport()) as scp:
            # 遍历本地文件夹
            for root, dirs, files in os.walk(local_folder):
                for file in files:
                    local_file = os.path.join(root, file)
                    relative_path = os.path.relpath(local_file, local_folder)
                    remote_file = os.path.join(remote_folder, relative_path)
                    remote_dir = os.path.dirname(remote_file)
                    
                    # 创建远程目录
                    ssh_client.exec_command(f'mkdir -p {remote_dir}')
                    
                    # 传输文件
                    scp.put(local_file, remote_file)
                    logging.info(f"Transferred {local_file} to {remote_file}")
            logging.info("File transfer completed successfully.")
    except Exception as e:
        logging.error(f"File transfer failed: {e}")
        raise

def main():
    # 配置连接信息
    hostname = '172.20.10.2'  # Raspberry Pi 的 IP 地址
    port = 22  # SSH 默认端口
    username = 'haitianrasp'  # 树莓派用户名
    password = 'qwer'  # 树莓派密码

    # 本地文件夹和树莓派目标目录
    local_folder = r'D:\Photogrammetry 2024\Hadlow\20240716 Hadlow\DJI_202407161308_001'  # Windows 中的图片数据集目录
    remote_folder = '/home/haitianrasp/Dataset/'  # 树莓派中的目标目录

    # 检查本地文件夹是否存在
    if not os.path.exists(local_folder):
        logging.error(f"Local folder does not exist: {local_folder}")
        raise FileNotFoundError(f"Local folder does not exist: {local_folder}")
    
    try:
        # 创建 SSH 连接
        ssh_client = create_ssh_client(hostname, port, username, password)

        # 传输文件
        transfer_files(ssh_client, local_folder, remote_folder)
    except Exception as e:
        logging.error(f"An error occurred: {e}")
    finally:
        if 'ssh_client' in locals() and ssh_client:
            ssh_client.close()
            logging.info("SSH connection closed.")

if __name__ == '__main__':
    main()

















