const fs=require('fs'),path=require('path');
const root=path.join(__dirname,'..'), dir=path.join(root,'Video');
const ext=/\.(mp4|webm|ogg|m4v|mov|mp3|m4a|wav|flac|aac)$/i;
const files=fs.readdirSync(dir,{withFileTypes:true}).filter(x=>x.isFile()&&ext.test(x.name)).map(x=>({name:x.name.replace(/\.[^.]+$/,'').replace(/[_-]+/g,' ').replace(/\s+/g,' ').trim(),url:'/Video/'+encodeURIComponent(x.name),type:/\.(mp3|m4a|wav|flac|aac)$/i.test(x.name)?'audio':'video'}));
fs.writeFileSync(path.join(root,'catalog.json'),JSON.stringify(files,null,2));
console.log('Indexed '+files.length+' media files');
