echo "Setting up Docker"

#uninstall previous version of docker if any
dpkg -l | grep -i docker && sudo apt-get purge -y docker-engine docker docker.io docker-ce docker-ce-cli && sudo apt-get autoremove -y --purge docker-engine docker docker.io docker-ce &&  sudo rm -rf /var/lib/docker /etc/docker && sudo rm /etc/apparmor.d/docker && sudo groupdel docker && sudo rm -rf /var/run/docker.sock

#install docker
sudo apt-get install -y docker-ce=18.06.1~ce~3-0~ubuntu
sudo groupadd docker && sudo usermod -aG docker $USER

echo "Build Malicious Container Image" 
docker build -t cve-2019-5736:malicious_image_POC ./malicious_image_POC

#stop Docker and restart AuditD so that no -1 namespace is appeard for container
sudo systemctl stop docker
echo "Stopping Docker..."

sudo systemctl restart auditd
echo "Restarting Audit..."
sleep 3

sudo systemctl start docker
echo "Docker Started..."
sleep 3

echo "Docker 18.06.1 setup completed..."

