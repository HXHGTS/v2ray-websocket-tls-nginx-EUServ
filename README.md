# v2ray-websocket-tls-nginx-EUServ

## 警告⚠：此技术仅限用于个人搭建游戏加速器使用！！！若用于其他违法目的，后果自负！！！

手动搭建v2ray服务器，并部署网页页面，支持cdn中转(本脚本用于支持EUServ低性能主机安装v2ray)

一句话执行(CentOS7):

`echo "nameserver 2001:67c:2b0::4" > /etc/resolv.conf && echo "nameserver 2001:67c:2b0::6" >> /etc/resolv.conf && yum install -y wget && wget https://cdn.jsdelivr.net/gh/HXHGTS/v2ray-websocket-tls-nginx-EUServ/v2ray -O v2ray && chmod +x v2ray && sudo ./v2ray`

CDN套用方法请参看[CDN套用方法](/cdn.md)

脚本生成的二维码可以用v2ray客户端扫描导入，VMESS链接可以直接导入v2ray客户端或在[这里](https://hxhgts.ml/ClashRuleTransfer/)生成Clash链接以导入Clash

### 安装前准备：

1.一个域名，与服务器ip做好dns解析

2.该域名必须提前申请SSL证书用于加密（后续考虑加入自动申请证书），将证书(*.cer/*.crt/*.pem)文件命名为1.pem，将私钥(*.key/*.pem)文件命名为2.pem，放在/root目录下(SSL证书申请:[腾讯云](https://console.cloud.tencent.com/ssl) [阿里云](https://common-buy.aliyun.com/?spm=5176.b5912525.0.0.3c07GExwGExwfv&commodityCode=cas) [FreeSSL](https://freessl.cn/))

3.脚本执行需要root权限登录系统

4.请在服务器防火墙放行tcp80(http)tcp443(https)端口(没动过防火墙就不要再改)
