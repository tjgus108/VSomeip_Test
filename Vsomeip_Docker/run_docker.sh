echo "###Docker Run Script Start###"
echo "=> Copy all Libraries and Sources to Docker Volume"
scp -r ./../lib ./install/
mkdir ./install/sample
scp ./../CMakeLists.txt ./install/
scp -r ./../src-gen ./install
scp -r ./../config ./install/
scp -r ./../src ./install
echo "=> Build docker image [Only very first time]"
docker build . -t vsomeip_test_img
echo "=> Run Docker"
docker run -it --name vsomeip_test -v $(pwd)/install:/Workspace/install -w /Workspace/install vsomeip_test_img 
