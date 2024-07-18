function mybombs
clear
backgrd=figure('Color',[1 1 1]);
restart=uicontrol('Style','pushbutton','BackgroundColor',[0.9 0.9 0.9],...
    'String','重来', 'Units','normalized','Position',[0.8 0.7 0.14 0.07])
flagon=uicontrol('Style','togglebutton','BackgroundColor',[0.9 0.9 0.9],...
    'String','插旗', 'Units','normalized','Position',[0.8 0.5 0.14 0.07]);
for i=1:8
    for j=1:8
        Bh(i,j)=uicontrol('Style','pushbutton',...
            'BackgroundColor',[0.8 0.8 0.8],...
            'Units','normalized',...
            'Position',[0.07+(j-1)*0.09 0.8-(i-1)*0.09 0.09 0.09],'FontSize',16);
        Bh(i,j).Callback=@click;
    end
end
restart.Callback=@rebegin;
    function rebegin(hobject,event)
        close all;
        mybombs;
    end
flagon.Callback=@button;
    function button(h,e)
        var=get(h,'value');
        if var==1
            for q=1:8
                for p=1:8
                    Bh(q,p).Callback=@flag;
                end
            end
        else
            for q=1:8
                for p=1:8
                    Bh(q,p).Callback=@click;
                end
            end
        end
    end

%布置地雷矩阵D
D=zeros(8);
while nnz(D)~=13
    hang=randi(8);
    lie=randi(8);
    D(hang,lie)=1;
end
D
%周围地雷数量矩阵num
S=zeros(10);
S(2:9,2:9)=D;
num=zeros(8);
for x=2:9
    for y=2:9
        num(x-1,y-1)=S(x-1,y-1)+S(x-1,y)+S(x-1,y+1)+S(x,y-1)+...
            S(x,y+1)+S(x+1,y-1) +S(x+1,y) +S(x,y+1) ;
    end
end
num

%扩充防止超出索引
Bhplus=ones(10,10);
Bhplus(:)=uicontrol('Style','text',...
    'BackgroundColor','w',...
    'Units','normalized',...
    'Position',[0.01 0.01 0.01 0.01]);
Bhplus(2:9,2:9)=Bh;
numplus=ones(10,10);
numplus(2:9,2:9)=num;
Dplus=ones(10,10);
Dplus(2:9,2:9)=D;

%建立判断矩阵用于判断是否标记数字,为0代表该处格子已被消除
judgeplus=ones(10);
jd=ones(10);%用于判断胜利条件
jd(:,1)=0;jd(1,:)=0;jd(10,:)=0;jd(:,10)=0;

%响应
    function flag(hobject,event)
        [i1,j1]=find(Bh==hobject);
        set(Bh(i1,j1),'string','旗');
    end
    function click(hobject,event)
        [i1,j1]=find(Bh==hobject);
        removerd(i1,j1);%周
        removelu(i1,j1);%围
        removeru(i1,j1);%无
        removeld(i1,j1);%雷
        numark;
        if D(i1,j1)==0&&num(i1,j1)~=0%不是雷且周围有雷
            set(Bh(i1,j1),'style','text','backgroundcolor','w','string',num(i1,j1));
            jd(i1+1,j1+1)=0;
        elseif D(i1,j1)==1%点到地雷
            set(backgrd,'Color',[0 0 0]);
            for v=1:8
                for u=1:8
                    if D(v,u)==1
                        set(Bh(v,u),'style','text','string','雷','backgroundcolor',[0.5 0.5 0.5]);
                    else
                        set(Bh(v,u),'style','text')
                    end
                end
            end
            set(Bh(i1,j1),'backgroundcolor','r');
        end
        win;
    end
%判断是否取胜
    function win
        if nnz(jd)==13
            for h=1:8
                for l=1:8
                    if D(h,l)==1
                        set(Bh(h,l),'style','text','string','旗');
                    end
                end
            end
        end
    end

%点击周围无雷时消除
%右下
    function removerd(i1,j1)
        %纵向消除向下消除
        if Dplus(i1+1,j1+1)==0&&numplus(i1+1,j1+1)==0&&i1<=8&&j1<=8
            set(Bhplus(i1+1,j1+1),'style','text','backgroundcolor','w');
            judgeplus(i1+1,j1+1)=0;
            jd(i1+1,j1+1)=0;
            removerd(i1+1,j1);
        end
        %横向消除向右消除
        if Dplus(i1+1,j1+1)==0&&numplus(i1+1,j1+1)==0&&i1<=8&&j1<=8
            set(Bhplus(i1+1,j1+1),'style','text','backgroundcolor','w');
            judgeplus(i1+1,j1+1)=0;
            jd(i1+1,j1+1)=0;
            removerd(i1,j1+1);
        end
    end

%左上
    function removelu(i1,j1)
        %纵向消除向上消除
        if Dplus(i1+1,j1+1)==0&&numplus(i1+1,j1+1)==0&&i1>=1&&j1>=1
            set(Bhplus(i1+1,j1+1),'style','text','backgroundcolor','w');
            judgeplus(i1+1,j1+1)=0;
            jd(i1+1,j1+1)=0;
            removelu(i1-1,j1);
        end
        %横向消除向左消除
        if Dplus(i1+1,j1+1)==0&&numplus(i1+1,j1+1)==0&&i1>=1&&j1>=1
            set(Bhplus(i1+1,j1+1),'style','text','backgroundcolor','w');
            judgeplus(i1+1,j1+1)=0;
            jd(i1+1,j1+1)=0;
            removelu(i1,j1-1);
        end
    end

%右上
    function removeru(i1,j1)
        %纵向消除向上消除
        if Dplus(i1+1,j1+1)==0&&numplus(i1+1,j1+1)==0&&i1>=1&&j1>=1
            set(Bhplus(i1+1,j1+1),'style','text','backgroundcolor','w');
            judgeplus(i1+1,j1+1)=0;
            jd(i1+1,j1+1)=0;
            removeru(i1-1,j1);
        end
        %横向消除向右消除
        if Dplus(i1+1,j1+1)==0&&numplus(i1+1,j1+1)==0&&i1<=8&&j1<=8
            set(Bhplus(i1+1,j1+1),'style','text','backgroundcolor','w');
            judgeplus(i1+1,j1+1)=0;
            jd(i1+1,j1+1)=0;
            removeru(i1,j1+1);
        end
    end

%左下
    function removeld(i1,j1)
        %纵向消除向下消除
        if Dplus(i1+1,j1+1)==0&&numplus(i1+1,j1+1)==0&&i1<=8&&j1<=8
            set(Bhplus(i1+1,j1+1),'style','text','backgroundcolor','w');
            judgeplus(i1+1,j1+1)=0;
            jd(i1+1,j1+1)=0;
            removeld(i1+1,j1);
        end
        %横向消除向左消除
        if Dplus(i1+1,j1+1)==0&&numplus(i1+1,j1+1)==0&&i1>=1&&j1>=1
            set(Bhplus(i1+1,j1+1),'style','text','backgroundcolor','w');
            judgeplus(i1+1,j1+1)=0;
            jd(i1+1,j1+1)=0;
            removeld(i1,j1-1);
        end
    end
%扫描一遍棋盘，消除'周围有地雷的格子'并标记数字
    function  numark
        ninejudge=ones(4,1);
        for a=1:8
            for b=1:8
                ninejudge(1)=judgeplus(a,b+1);
                ninejudge(2)=judgeplus(a+1,b);
                ninejudge(3)=judgeplus(a+1,b+2);
                ninejudge(4)=judgeplus(a+2,b+1);
                if any(ninejudge(:)==0)&&num(a,b)~=0&&D(a,b)~=1
                    set(Bh(a,b),'style','text','backgroundcolor','w','string',num(a,b));
                    jd(a+1,b+1)=0;
                end
            end
        end
    end
end





