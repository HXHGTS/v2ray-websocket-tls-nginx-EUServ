﻿#include <stdio.h>
#include <stdlib.h>


FILE* config,* cer;
char uuid[40],sni[30];
int mode;

int main(){
Menu:UI();
    system("clear");
    if (mode == 1) {
        install_v2ray();
        goto Menu;
    }
    else if (mode == 2) {
        system("systemctl stop v2ray");
        system("systemctl stop nginx");
        system("systemctl start v2ray");
        system("systemctl start nginx");
        printf("正在检测v2ray与nginx运行状态，以下输出不为空则运行正常！\n");
        printf("--------------以下输出不为空则v2ray运行正常------------------\n");
        system("ss -lp | grep v2ray");
        printf("\n--------------以下输出不为空则nginx运行正常------------------\n");
        system("ss -lp | grep nginx");
        printf("--------------------------------------------------------\n");
        goto Menu;
    }
    else if (mode == 3) {
        printf("v2ray二维码:\n\n");
        system("qrencode -t ansiutf8 < /usr/local/etc/v2ray/vmess.txt");
        printf("\n\n");
        printf("Vmess链接:\n\n");
        system("bash /usr/local/etc/v2ray/code_gen.sh");
        printf("\n");
        goto Menu;
    }
    else if (mode == 4) {
        system("vi /usr/local/etc/v2ray/config.json");
        system("systemctl restart v2ray");
        system("systemctl restart nginx");
        printf("正在检测v2ray与nginx运行状态，以下输出不为空则运行正常！\n");
        printf("--------------以下输出不为空则v2ray运行正常------------------\n");
        system("ss -lp | grep v2ray");
        printf("\n--------------以下输出不为空则nginx运行正常------------------\n");
        system("ss -lp | grep nginx");
        printf("--------------------------------------------------------\n");
        goto Menu;
    }
    else if (mode == 5) {
        system("vi /etc/nginx/conf.d/default.conf");
        system("systemctl restart v2ray");
        system("systemctl restart nginx");
        printf("正在检测v2ray与nginx运行状态，以下输出不为空则运行正常！\n");
        printf("--------------以下输出不为空则v2ray运行正常------------------\n");
        system("ss -lp | grep v2ray");
        printf("\n--------------以下输出不为空则nginx运行正常------------------\n");
        system("ss -lp | grep nginx");
        printf("--------------------------------------------------------\n");
        goto Menu;
    }
    else if (mode == 6) {
        if (fopen("/root/1.pem", "r") == NULL || fopen("/root/2.pem", "r") == NULL) {
            printf("检测到证书与私钥文件未按照规定方式放置于根目录，强制退出！\n");
            exit(0);
        }
        printf("请输入已绑定此服务器ip的新域名:");
        scanf("%s", sni);
        config = fopen("/usr/local/etc/sni.conf", "w");
        fprintf(config, "%s", sni);
        fclose(config);
        printf("正在复制SSL证书与私钥. . .\n");
        system("cp -rf /root/1.pem /usr/local/etc/v2ray/certificate.pem");
        system("cp -rf /root/2.pem /usr/local/etc/v2ray/private.pem");
        config = fopen("/usr/local/etc/v2ray/uuid.conf", "r");
        fscanf(config, "%s", uuid);
        fclose(config);
        printf("正在配置html网页. . .\n");
        config = fopen("/etc/nginx/conf.d/default.conf", "w");
        fprintf(config, "server {\n");
        fclose(config);
        config = fopen("/etc/nginx/conf.d/default.conf", "a");
        fprintf(config, "    server_name %s;\n", sni);
        fclose(config);
        system("curl https://raw.githubusercontent.com/HXHGTS/v2ray-websocket-tls-nginx-EUServ/main/default.conf >> /etc/nginx/conf.d/default.conf");
        system("systemctl restart nginx");
        QRCodeGen();
        printf("正在检测v2ray与nginx运行状态，以下输出不为空则运行正常！\n");
        printf("--------------以下输出不为空则v2ray运行正常------------------\n");
        system("ss -lp | grep v2ray");
        printf("\n--------------以下输出不为空则nginx运行正常------------------\n");
        system("ss -lp | grep nginx");
        printf("--------------------------------------------------------\n");
        printf("v2ray部署完成！\n");
        printf("v2ray二维码:\n\n");
        system("qrencode -t ansiutf8 < /usr/local/etc/v2ray/vmess.txt");
        printf("\n\n");
        printf("Vmess链接:\n\n");
        system("bash /usr/local/etc/v2ray/code_gen.sh");
        goto Menu;
    }
    else if (mode == 7) {
        printf("正在更新v2ray主程序. . .\n");
        system("systemctl stop v2ray");
        system("systemctl stop nginx");
        system("wget https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-release.sh -O install-release.sh");
        system("chmod +x install-release.sh");
        system("bash install-release.sh");
        system("systemctl start v2ray");
        system("systemctl start nginx");
        system("rm -rf install-release.sh");
        printf("v2ray主程序更新完成！\n");
        printf("正在检测v2ray与nginx运行状态，以下输出不为空则运行正常！\n");
        printf("--------------以下输出不为空则v2ray运行正常------------------\n");
        system("ss -lp | grep v2ray");
        printf("\n--------------以下输出不为空则nginx运行正常------------------\n");
        system("ss -lp | grep nginx");
        printf("--------------------------------------------------------\n");
        goto Menu;
    }
    else if (mode == 8) {
        system("systemctl stop v2ray");
        system("systemctl stop nginx");
        goto Menu;
    }
    else {
        exit(0);
    }
    return 0;
}

int UI() {
    printf("-----------------------------------------------------------\n");
    printf("----------------------v2ray安装工具-----------------------\n");
    printf("-----------------------------------------------------------\n");
    printf("安装前或需要更新SSL证书，请将证书(*.cer/*.crt/*.pem)与私钥(*.key/*.pem)分别命名为1.pem与2.pem，上传至服务器/root目录\n");
    printf("-----------------------------------------------------------\n");
    printf("----------------------当前Kernel版本-----------------------\n");
    system("uname -sr");
    printf("-----------------------------------------------------------\n");
    printf("1.安装v2ray\n2.运行v2ray\n3.显示配置\n4.修改v2ray配置\n5.修改nginx配置\n6.更新域名与SSL证书\n7.更新v2ray\n8.关闭v2ray\n0.退出\n");
    printf("-----------------------------------------------------------\n");
    printf("请输入:");
    scanf("%d", &mode);
    return 0;
}

int install_v2ray() {
    KernelUpdate(); 
    config = fopen("/usr/local/etc/sni.conf", "r");
    fscanf(config, "%s", sni);
    fclose(config);
    system("setenforce 0");
    system("yum install -y curl uuidgen unzip epel-release nginx bind-utils qrencode");
    printf("正在运行v2ray安装脚本. . .\n");
    system("wget https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-release.sh -O install-release.sh");
    system("chmod +x install-release.sh");
    system("bash install-release.sh");
    system("sleep 3");
    system("rm -rf install-release.sh");
    printf("正在复制SSL证书与私钥. . .\n");
    system("cp -rf /root/1.pem /usr/local/etc/v2ray/certificate.pem");
    system("cp -rf /root/2.pem /usr/local/etc/v2ray/private.pem");
    printf("正在生成配置文件. . .\n");
    system("curl https://raw.githubusercontent.com/HXHGTS/v2ray-websocket-tls-nginx-EUServ/main/config.json.1 > /usr/local/etc/v2ray/config.json");
    printf("正在生成UUID. . .\n");
    system("uuidgen > /usr/local/etc/v2ray/uuid.conf");
    config = fopen("/usr/local/etc/v2ray/uuid.conf", "r");
    fscanf(config, "%s", uuid);
    fclose(config);
    config = fopen("/usr/local/etc/v2ray/config.json", "a");
    fprintf(config, "       \"id\": \"%s\",  \n", uuid);
    fclose(config);
    system("curl https://raw.githubusercontent.com/HXHGTS/v2ray-websocket-tls-nginx-EUServ/main/config.json.2 >> /usr/local/etc/v2ray/config.json");
    printf("正在配置html网页. . .\n");
    config = fopen("/etc/nginx/conf.d/default.conf", "w");
    fprintf(config, "server {\n");
    fclose(config);
    config = fopen("/etc/nginx/conf.d/default.conf", "a");
    fprintf(config, "    server_name %s;\n",sni);
    fclose(config);
    system("curl https://raw.githubusercontent.com/HXHGTS/v2ray-websocket-tls-nginx-EUServ/main/default.conf >> /etc/nginx/conf.d/default.conf");
    system("wget https://github.com/HXHGTS/v2ray-websocket-tls-nginx-EUServ/raw/main/html.zip -O /usr/share/nginx/html/html.zip");
    system("unzip -o /usr/share/nginx/html/html.zip -d /usr/share/nginx/html");
    system("rm -f /usr/share/nginx/html/html.zip");
    printf("正在启动v2ray并将v2ray写入开机引导项. . .\n");
    system("systemctl enable v2ray");
    system("systemctl start v2ray");
    printf("正在启动nginx并将nginx写入开机引导项. . .\n");
    system("systemctl enable nginx");
    system("systemctl start nginx");
    system("mkdir /etc/systemd/system/nginx.service.d");
    system("printf \"[Service]\nExecStartPost=/bin/sleep 0.1\n\" > /etc/systemd/system/nginx.service.d/override.conf");
    system("systemctl daemon-reload");
    system("systemctl restart nginx.service");
    system("setsebool -P httpd_can_network_connect 1");
    QRCodeGen();
    printf("正在检测v2ray与nginx运行状态，以下输出不为空则运行正常！\n");
    printf("--------------以下输出不为空则v2ray运行正常------------------\n");
    system("ss -lp | grep v2ray");
    printf("\n--------------以下输出不为空则nginx运行正常------------------\n");
    system("ss -lp | grep nginx");
    printf("--------------------------------------------------------\n");
    printf("v2ray部署完成！\n");
    printf("v2ray二维码:\n\n");
    system("qrencode -t ansiutf8 < /usr/local/etc/v2ray/vmess.txt");
    printf("\n\n");
    printf("Vmess链接:\n\n");
    system("bash /usr/local/etc/v2ray/code_gen.sh");
    return 0;
}

int QRCodeGen() {
    config = fopen("/usr/local/etc/v2ray/code_gen.sh", "w");
    fprintf(config, "#!/bin/bash\n");
    fprintf(config, "VMESSCODE=$(base64 -w 0 << EOF\n");
    fprintf(config, "    {\n");
    fprintf(config, "      \"v\": \"2\",\n");
    fprintf(config, "      \"ps\": \"v2ray\",\n");
    fprintf(config, "      \"add\": \"%s\",\n",sni);//Addr
    fprintf(config, "      \"port\": \"443\",\n");
    fprintf(config, "      \"id\": \"%s\",\n",uuid);//UUID
    fprintf(config, "      \"aid\": \"0\",\n");
    fprintf(config, "      \"net\": \"ws\",\n");
    fprintf(config, "      \"type\": \"none\",\n");
    fprintf(config, "      \"host\": \"%s\",\n",sni);
    fprintf(config, "      \"path\": \"/iso\",\n");
    fprintf(config, "      \"tls\": \"tls\"\n");
    fprintf(config, "    }\n");
    fprintf(config, "EOF\n");
    fprintf(config, "    )\n");
    fprintf(config, "echo vmess://${VMESSCODE}\n");
    fclose(config);
    system("bash /usr/local/etc/v2ray/code_gen.sh > /usr/local/etc/v2ray/vmess.txt");
    return 0;
}

int KernelUpdate() {
    if (fopen("/root/1.pem", "r") == NULL || fopen("/root/2.pem", "r") == NULL) {
    printf("检测到证书与私钥文件未按照规定方式放置于根目录，强制退出！\n");
    exit(0);
    }
    printf("请输入已绑定此服务器ip的域名:");
    scanf("%s", sni);
    config = fopen("/usr/local/etc/sni.conf", "w");
    fprintf(config, "%s", sni);
    fclose(config);
    return 0;
}
