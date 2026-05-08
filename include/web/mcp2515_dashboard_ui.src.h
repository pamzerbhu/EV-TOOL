#pragma once
#ifdef ESP_PLATFORM
#include "platform/espidf_runtime.h"
#else
#include <Arduino.h>
#endif

static const char DASH_HTML[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html lang="en" data-theme="dark">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1,user-scalable=no">
<title>ev-open-can-tools</title>
<style>
*{margin:0;padding:0;box-sizing:border-box}
[data-theme="dark"]{
  --bg:#0d0d0d;--bg2:var(--bg);--card:#161616;--card2:#1e1e1e;
  --bd:#2a2a2a;--bd2:#333;
  --tx:#f0f0f0;--tx2:#999;--tx3:#555;
  --acc:#5b8fff;--accBg:rgba(91,143,255,.1);--accBd:rgba(91,143,255,.25);
  --ok:#3dba72;--okBg:rgba(61,186,114,.1);
  --err:#ff4f4f;--errBg:rgba(255,79,79,.08);--errBd:rgba(255,79,79,.2);
  --warn:#f5a623;
}
[data-theme="light"]{
  --bg:#f5f5f5;--bg2:var(--bg);--card:#fff;--card2:#f0f0f0;
  --bd:#e0e0e0;--bd2:#ccc;
  --tx:#111;--tx2:#555;--tx3:#999;
  --acc:#2563eb;--accBg:rgba(37,99,235,.08);--accBd:rgba(37,99,235,.2);
  --ok:#16a34a;--okBg:rgba(22,163,74,.08);
  --err:#dc2626;--errBg:rgba(220,38,38,.06);--errBd:rgba(220,38,38,.18);
  --warn:#d97706;
}
html{scroll-behavior:smooth}
body{background:var(--bg);color:var(--tx);font-family:-apple-system,BlinkMacSystemFont,'Segoe UI',sans-serif;
  min-height:100vh;max-width:480px;margin:0 auto;font-size:14px;line-height:1.5;
  transition:background .2s,color .2s}

/* Header */
.hdr{padding:20px 16px 0;display:flex;flex-direction:column;gap:4px}
.hdr-top{display:flex;align-items:center;justify-content:space-between}
.hdr-left{display:flex;align-items:center;gap:8px;flex-wrap:wrap;min-width:0}
.hdr-title{font-size:20px;font-weight:700;color:var(--tx)}
.hw-badge{padding:3px 8px;border-radius:5px;font-size:11px;font-weight:600;
  background:var(--accBg);border:1px solid var(--accBd);color:var(--acc)}
.gtw-badge{padding:3px 8px;border-radius:5px;font-size:11px;font-weight:600;
  background:var(--card);border:1px solid var(--bd2);color:var(--tx2)}
.gtw-badge.known{color:var(--ok);border-color:rgba(61,186,114,.25);background:var(--okBg)}
.theme-btn{padding:6px 10px;border:1px solid var(--bd2);border-radius:8px;
  background:var(--card);color:var(--tx2);font-size:12px;cursor:pointer;
  display:flex;align-items:center;gap:4px;transition:all .2s}
.theme-btn:hover{border-color:var(--acc);color:var(--acc)}
.hdr-status{display:flex;align-items:center;gap:6px;font-size:12px;color:var(--tx2)}
.sdot{width:7px;height:7px;border-radius:50%;flex-shrink:0;transition:all .4s}
.dot-on{background:var(--ok);box-shadow:0 0 8px var(--ok)}
.dot-off{background:var(--err)}
.dot-warn{background:var(--warn)}

/* FPS bar */
.fps-bar{margin:14px 16px 0;height:3px;background:var(--bd);border-radius:2px;overflow:hidden}
.fps-fill{height:100%;background:var(--acc);border-radius:2px;transition:width .5s;width:0%}

/* Status grid */
.stat-grid{display:grid;grid-template-columns:1fr 1fr 1fr;gap:8px;margin:14px 16px 0}
.stat{background:var(--card);border:1px solid var(--bd);border-radius:10px;padding:10px 12px}
.stat-lbl{font-size:10px;color:var(--tx3);text-transform:uppercase;letter-spacing:.8px;margin-bottom:3px}
.stat-val{font-size:14px;font-weight:600;color:var(--tx)}
.v-ok{color:var(--ok)}.v-err{color:var(--err)}.v-acc{color:var(--acc)}.v-dim{color:var(--tx3)}.v-warn{color:var(--warn)}
.stat-wide{grid-column:span 3}
.sys-grid{display:grid;grid-template-columns:1fr 1fr;gap:8px}
.sys-item{background:var(--bg2);border:1px solid var(--bd);border-radius:8px;padding:8px 10px;min-width:0}
.sys-lbl{font-size:10px;color:var(--tx3);text-transform:uppercase;letter-spacing:.5px;margin-bottom:2px}
.sys-val{font-size:12px;font-weight:600;color:var(--tx);word-break:break-word}
.sys-wide{grid-column:span 2}
.sys-bar{height:4px;background:var(--bd);border-radius:2px;overflow:hidden;margin-top:6px}
.sys-fill{height:100%;background:var(--acc);border-radius:2px;transition:width .3s;width:0}
.sys-monitor{display:flex;align-items:center;justify-content:flex-end;gap:8px}
.sys-monitor span{white-space:nowrap}
.sys-monitor .tgl{margin-left:0}
/* Divider */
hr{border:none;border-top:1px solid var(--bd);margin:16px}

/* Cards */
.card{background:var(--card);border:1px solid var(--bd);border-radius:12px;padding:16px;margin:0 16px 12px;overflow:hidden}
.card-hdr{display:grid;grid-template-columns:minmax(0,1fr) auto auto;align-items:center;column-gap:8px;margin-bottom:14px}
.card-title{font-size:13px;font-weight:600;color:var(--tx);text-transform:uppercase;letter-spacing:.5px;min-width:0}
.card-meta{font-size:11px;color:var(--tx3);justify-self:end;text-align:right;min-width:0}
.card-min-btn{padding:4px 8px;font-size:10px;justify-self:end}
.card.collapsed{padding-bottom:12px}
.card.collapsed .card-hdr{margin-bottom:0}
.card.collapsed>:not(.card-hdr){display:none !important}
.subsec{margin-top:14px;padding-top:12px;border-top:1px solid var(--bd)}
.subsec:first-child{margin-top:0;padding-top:0;border-top:none}
.subsec-head{display:grid;grid-template-columns:minmax(110px,1fr) auto auto;align-items:center;column-gap:8px;margin-bottom:8px}
.subsec-title{font-size:13px;font-weight:600;color:var(--tx);min-width:0;word-break:keep-all}
.title-help{display:inline-flex;align-items:center;justify-content:center;width:16px;height:16px;margin-left:6px;border:1px solid var(--bd2);border-radius:50%;font-size:10px;font-weight:700;color:var(--tx3);cursor:pointer;vertical-align:middle;line-height:1;background:transparent}
.title-help:hover{border-color:var(--accBd);color:var(--acc);background:var(--accBg)}
.info-box{margin-bottom:10px;padding:10px 12px;background:var(--bg2);border:1px solid var(--bd);border-radius:9px;font-size:12px;color:var(--tx3);line-height:1.6}
.info-box a{color:var(--acc);text-decoration:none}
.inline-help-panel{display:none;margin:8px 0 0;padding:10px 12px;background:var(--bg2);border:1px solid var(--bd);border-radius:9px;font-size:12px;color:var(--tx3);line-height:1.6}
.inline-help-panel.show{display:block}
.subsec-meta{font-size:11px;color:var(--tx3);justify-self:end;text-align:right;min-width:0}
.subsec-btn{padding:4px 8px;font-size:10px;justify-self:end}
.subsec.collapsed .subsec-head{margin-bottom:0}
.subsec.collapsed .subsec-body{display:none}

/* HW seg */
.hw-seg{display:flex;background:var(--card2);border:1px solid var(--bd);border-radius:9px;padding:3px;gap:2px}
.hw-btn{flex:1;padding:8px;border:none;border-radius:7px;font-size:12px;font-weight:600;
  cursor:pointer;background:transparent;color:var(--tx2);transition:all .18s;font-family:inherit}
.hw-btn.active{background:var(--card);color:var(--acc);border:1px solid var(--accBd);
  box-shadow:0 1px 4px rgba(0,0,0,.15)}
.hw-btn:hover:not(.active){background:var(--bd);color:var(--tx)}
.profile-wrap{margin-top:12px}
.profile-label{font-size:11px;color:var(--tx3);margin-bottom:6px}
.profile-group.hidden{display:none}
.profile-note{font-size:10px;color:var(--tx3);margin-top:6px}

/* Speed pills */
.pills{display:flex;gap:6px;flex-wrap:wrap}
/* Settings rows */
.setting-row{display:flex;align-items:center;justify-content:space-between;
  padding:12px 0;border-bottom:1px solid var(--bd)}
.setting-row:last-of-type{border-bottom:none;padding-bottom:0}
.setting-row:first-of-type{padding-top:0}
.setting-info{flex:1;min-width:0}
.setting-name{font-size:13px;font-weight:500;color:var(--tx)}
.setting-desc{font-size:11px;color:var(--tx3);margin-top:2px}
.hw4-only.hidden{display:none}

/* Toggle */
.tgl{position:relative;width:44px;height:24px;flex-shrink:0;margin-left:12px}
.tgl input{opacity:0;width:0;height:0;position:absolute}
.tgl-track{position:absolute;inset:0;background:var(--bd2);border-radius:24px;cursor:pointer;transition:all .22s}
.tgl-thumb{position:absolute;top:3px;left:3px;width:18px;height:18px;background:#fff;
  border-radius:50%;transition:all .22s;box-shadow:0 1px 3px rgba(0,0,0,.3)}
.tgl input:checked~.tgl-track{background:var(--acc)}
.tgl input:checked~.tgl-track .tgl-thumb{transform:translateX(20px)}
.tgl input:disabled~.tgl-track{opacity:.35;cursor:not-allowed}

/* Sniffer */
.sniff-ctrl{display:flex;gap:6px;margin-bottom:8px}
.sniff-input{flex:1;background:var(--bg);border:1px solid var(--bd);border-radius:8px;
  padding:7px 10px;color:var(--tx);font-size:12px;font-family:inherit;transition:border .2s}
.sniff-input{width:100%;min-width:0;box-sizing:border-box;} 
.sniff-input:focus{outline:none;border-color:var(--acc)}
.sniff-input::placeholder{color:var(--tx3)}
.sniff-btn{padding:7px 12px;background:transparent;border:1px solid var(--bd);border-radius:8px;
  color:var(--tx2);font-size:11px;font-weight:600;cursor:pointer;transition:all .18s;font-family:inherit}
.sniff-btn.paused{border-color:var(--warn);color:var(--warn)}
.sniff-btn:hover:not(.paused){border-color:var(--bd2);color:var(--tx)}
.gateway-mode-btn.active{background:var(--accBg);border-color:var(--acc);color:var(--acc);box-shadow:0 0 0 1px var(--accBd) inset}
.gateway-mode-btn.saving{opacity:.65;pointer-events:none}
.sniff-box{background:var(--bg);border:1px solid var(--bd);border-radius:9px;
  max-height:250px;overflow-y:auto;font-family:'SF Mono','Courier New',monospace}
.sniff-box::-webkit-scrollbar{width:4px}
.sniff-box::-webkit-scrollbar-thumb{background:var(--bd2);border-radius:4px}
.sniff-row{display:grid;grid-template-columns:38px 72px 1fr;gap:8px;
  padding:6px 10px;border-bottom:1px solid var(--bd);font-size:11px;align-items:start}
.sniff-row:last-child{border-bottom:none}
.sniff-row.hi{border-left:2px solid var(--acc);padding-left:8px}
.s-ts{color:var(--tx3);font-size:10px;padding-top:1px}
.s-id{color:var(--acc);font-weight:700}
.s-data{color:var(--tx2);word-break:break-all}
.s-name{color:var(--ok);font-size:10px;margin-top:2px}

/* EFLG */
.eflg-row{display:flex;flex-wrap:wrap;gap:5px;margin-top:10px}
.eflg-pill{padding:3px 8px;border-radius:5px;font-size:10px;font-weight:600;letter-spacing:.3px}
.eflg-ok{background:var(--okBg);color:var(--ok)}
.eflg-warn{background:rgba(245,166,35,.1);color:var(--warn)}
.eflg-err{background:var(--errBg);color:var(--err)}

/* Mux table */
.mux-tbl{width:100%;border-collapse:collapse;font-size:12px;margin-top:10px}
.mux-tbl th{color:var(--tx3);font-size:10px;text-transform:uppercase;letter-spacing:.8px;
  text-align:left;padding:4px 8px;border-bottom:1px solid var(--bd);font-weight:500}
.mux-tbl td{padding:5px 8px;color:var(--tx2);border-bottom:1px solid var(--bd)}
.mux-tbl tr:last-child td{border-bottom:none}
.mux-tbl td:first-child{color:var(--acc);font-weight:600}

/* Last write check */
.probe-status{font-size:13px;font-weight:600}
.probe-note{font-size:11px;color:var(--tx3);line-height:1.6;margin-top:10px}
.probe-block{margin-top:12px;padding-top:12px;border-top:1px solid var(--bd)}
.probe-meta{font-size:11px;color:var(--tx3);margin-bottom:4px}
.probe-label{font-size:10px;color:var(--tx3);text-transform:uppercase;letter-spacing:.8px;margin-bottom:6px}
.probe-hex{font-family:'SF Mono','Courier New',monospace;font-size:12px;color:var(--tx2);word-break:break-all}

/* Buttons */
.btn-row{display:flex;gap:8px;margin-top:14px}
.btn{flex:1;padding:10px;border:1px solid;border-radius:9px;background:transparent;
  font-family:inherit;font-size:12px;font-weight:600;cursor:pointer;transition:all .18s;letter-spacing:.3px}
.btn-stop{border-color:var(--errBd);color:var(--err)}
.btn-stop:hover{background:var(--errBg)}
.btn-reboot{border-color:var(--bd2);color:var(--tx2)}
.btn-reboot:hover{border-color:var(--acc);color:var(--acc)}

/* Confirm modal */
.modal-backdrop{position:fixed;inset:0;display:none;align-items:center;justify-content:center;
  padding:16px;background:rgba(0,0,0,.55);z-index:9999}
.modal-card{width:min(100%,360px);background:var(--card);border:1px solid var(--bd2);
  border-radius:12px;padding:16px;box-shadow:0 16px 40px rgba(0,0,0,.35)}
.modal-title{font-size:14px;font-weight:700;color:var(--tx)}
.modal-msg{margin-top:8px;font-size:12px;color:var(--tx2);line-height:1.6;white-space:pre-wrap}
.modal-actions{display:flex;justify-content:flex-end;gap:8px;margin-top:14px}
.modal-btn-primary{background:var(--accBg);border-color:var(--accBd);color:var(--acc)}
.modal-btn-primary:hover{background:var(--acc);color:#fff}
.dns-modal-card{width:min(100%,640px)}
.dns-modal-list{margin-top:10px;max-height:60vh;overflow:auto;border:1px solid var(--bd);border-radius:9px;padding:8px;background:var(--bg)}
.dns-row{display:grid;grid-template-columns:minmax(0,1fr) auto;gap:10px;align-items:center;padding:10px 8px;border-bottom:1px solid var(--bd)}
.dns-row:last-child{border-bottom:none}
.dns-domain{min-width:0;overflow:hidden;text-overflow:ellipsis;color:var(--tx);font-family:'SF Mono','Courier New',monospace;font-size:12px}
.dns-count{color:var(--tx3);font-size:10px;margin-left:6px}
.dns-state{font-size:11px;font-weight:600;white-space:nowrap}
.dns-state.err{color:var(--err)}
.dns-state.ok{color:var(--ok)}
.dns-state.dim{color:var(--tx3)}

/* OTA upload */
.ota-drop{border:2px dashed var(--bd2);border-radius:10px;padding:24px 16px;
  text-align:center;cursor:pointer;transition:all .2s;background:var(--bg)}
.ota-drop:hover,.ota-drop.drag{border-color:var(--acc);background:var(--accBg)}
.ota-drop input{display:none}
.ota-icon{font-size:24px;margin-bottom:8px}
.ota-text{font-size:13px;font-weight:500;color:var(--tx2);margin-bottom:3px}
.ota-sub{font-size:11px;color:var(--tx3)}
.ota-progress{margin-top:12px;display:none}
.ota-bar{height:4px;background:var(--bd);border-radius:2px;overflow:hidden;margin-bottom:6px}
.ota-fill{height:100%;background:var(--acc);border-radius:2px;transition:width .3s;width:0%}
.ota-status{font-size:11px;color:var(--acc);text-align:center}
.ota-btn{width:100%;margin-top:10px;padding:10px;border:1px solid var(--accBd);border-radius:9px;
  background:var(--accBg);color:var(--acc);font-family:inherit;font-size:13px;font-weight:600;
  cursor:pointer;transition:all .2s;display:none}
.ota-btn:hover{background:var(--acc);color:#fff}

/* Log */
.log-box{background:var(--bg);border:1px solid var(--bd);border-radius:9px;padding:10px 12px;
  font-family:'SF Mono','Courier New',monospace;font-size:11px;color:var(--tx2);
  max-height:180px;overflow-y:auto;line-height:1.9;white-space:pre-wrap;word-break:break-all}
.log-box::-webkit-scrollbar{width:4px}
.log-box::-webkit-scrollbar-thumb{background:var(--bd2);border-radius:4px}
.lf{color:var(--ok)}.lh{color:var(--acc)}.le{color:var(--err)}.lc{color:var(--warn)}.lo{color:var(--tx2)}

/* Recorder */
.rec-bar{height:4px;background:var(--bd);border-radius:2px;overflow:hidden;margin-bottom:6px}
.rec-fill{height:100%;background:var(--err);border-radius:2px;transition:width .3s;width:0%}
.rec-info{display:flex;justify-content:space-between;font-size:11px;color:var(--tx3);margin-bottom:10px}

/* Warning */
.warn-bar{margin:0 16px 14px;padding:10px 14px;border-radius:9px;
  background:var(--errBg);border:1px solid var(--errBd);font-size:11px;color:var(--err);line-height:1.7}
.foot{text-align:center;padding:8px 16px 20px;font-size:11px;color:var(--tx3)}
body:not(.can-debug-on) .can-debug-panel{display:none !important}
</style>
</head>
<body>

<div class="hdr">
  <div class="hdr-top">
    <div class="hdr-left">
      <div class="hdr-title">ev-open-can-tools</div>
      <span class="hw-badge" id="hw-badge">HW3</span>
      <span class="gtw-badge" id="gtw-badge" title="GTW_autopilot">GTW &mdash;</span>
    </div>
    <button class="theme-btn" onclick="toggleLanguage()" id="lang-btn">中文</button>
    <button class="theme-btn" onclick="toggleTheme()" id="theme-btn">&#9788; Light</button>
  </div>
  <div class="hdr-status">
    <span class="sdot dot-off" id="dot"></span>
    <span id="hdr-desc">Waiting for CAN frames</span>
  </div>
</div>

<div class="fps-bar"><div class="fps-fill" id="fps-fill"></div></div>

<div class="stat-grid">
  <div class="stat"><div class="stat-lbl">CAN Bus</div><div class="stat-val" id="s-can">Offline</div></div>
  <div class="stat"><div class="stat-lbl">Injection</div><div class="stat-val v-dim" id="s-inj">—</div></div>
  <div class="stat"><div class="stat-lbl" title="Frames received per second">CAN Frame Rate</div><div class="stat-val v-dim" id="s-fps">0.0 Hz</div></div>
  <div class="stat"><div class="stat-lbl">RX</div><div class="stat-val v-acc" id="s-rx">0</div></div>
  <div class="stat"><div class="stat-lbl">TX</div><div class="stat-val v-acc" id="s-tx">0</div></div>
  <div class="stat"><div class="stat-lbl">TX Errors</div><div class="stat-val v-dim" id="s-txerr">0</div></div>
  <div class="stat"><div class="stat-lbl">Follow dist</div><div class="stat-val v-dim" id="s-fd">—</div></div>
  <div class="stat"><div class="stat-lbl">Profile</div><div class="stat-val v-dim" id="s-prof">—</div></div>
  <div class="stat"><div class="stat-lbl">Limit Offset</div><div class="stat-val v-dim" id="s-soff">0</div></div>
  <div class="stat"><div class="stat-lbl">Uptime</div><div class="stat-val v-dim" id="s-up">0s</div></div>
  <button class="btn btn-stop" id="btn-stop" style="display:none" onclick="emergencyStop()">Stop Injecting</button>
  <button class="btn" id="btn-resume" style="display:none;background:var(--accBg);color:var(--acc);border:1px solid var(--accBd)" onclick="resumeInj()">Resume Injection</button>
  <button class="btn btn-reboot" onclick="reboot()">Reboot</button>
</div>

<div style="height:12px"></div>

<div class="card">
  <div class="card-hdr">
    <div class="card-title">System Status <span class="title-help" onclick="return toggleHelp(this,event)" title="Hardware and runtime health reported by the ESP32 firmware.">?</span></div>
    <div class="card-meta sys-monitor"><span id="sys-summary">Monitoring off</span><label class="tgl" title="Enable live hardware status sampling"><input type="checkbox" id="sys-monitor-tgl" onchange="toggleSystemMonitor()"><div class="tgl-track"><div class="tgl-thumb"></div></div></label></div>
  </div>
  <div class="sys-grid">
    <div class="sys-item"><div class="sys-lbl">Chip</div><div class="sys-val" id="sys-chip">--</div></div>
    <div class="sys-item"><div class="sys-lbl">CPU</div><div class="sys-val" id="sys-cpu">--</div></div>
    <div class="sys-item sys-wide">
      <div class="sys-lbl">CPU Load</div><div class="sys-val" id="sys-cpu-load">--</div>
      <div class="sys-bar"><div class="sys-fill" id="sys-cpu0-fill"></div></div>
      <div class="sys-bar" style="margin-top:4px"><div class="sys-fill" id="sys-cpu1-fill"></div></div>
    </div>
    <div class="sys-item sys-wide"><div class="sys-lbl">Board Specs</div><div class="sys-val" id="sys-board">--</div></div>
    <div class="sys-item"><div class="sys-lbl">Temperature</div><div class="sys-val" id="sys-temp">--</div></div>
    <div class="sys-item"><div class="sys-lbl">Reset</div><div class="sys-val" id="sys-reset">--</div></div>
    <div class="sys-item sys-wide">
      <div class="sys-lbl">Heap RAM</div><div class="sys-val" id="sys-heap">--</div>
      <div class="sys-bar"><div class="sys-fill" id="sys-heap-fill"></div></div>
    </div>
    <div class="sys-item"><div class="sys-lbl">Largest Block</div><div class="sys-val" id="sys-largest">--</div></div>
    <div class="sys-item"><div class="sys-lbl">Min Free Heap</div><div class="sys-val" id="sys-minheap">--</div></div>
    <div class="sys-item"><div class="sys-lbl">PSRAM</div><div class="sys-val" id="sys-psram">--</div></div>
    <div class="sys-item"><div class="sys-lbl">Tasks</div><div class="sys-val" id="sys-tasks">--</div></div>
    <div class="sys-item sys-wide">
      <div class="sys-lbl">Flash</div><div class="sys-val" id="sys-flash">--</div>
      <div class="sys-bar"><div class="sys-fill" id="sys-app-fill"></div></div>
    </div>
    <div class="sys-item sys-wide">
      <div class="sys-lbl">SPIFFS</div><div class="sys-val" id="sys-spiffs">--</div>
      <div class="sys-bar"><div class="sys-fill" id="sys-spiffs-fill"></div></div>
    </div>
    <div class="sys-item"><div class="sys-lbl">WiFi RSSI</div><div class="sys-val" id="sys-rssi">--</div></div>
    <div class="sys-item"><div class="sys-lbl">WiFi Mode</div><div class="sys-val" id="sys-wifi-mode">--</div></div>
    <div class="sys-item"><div class="sys-lbl">AP Clients</div><div class="sys-val" id="sys-apclients">--</div></div>
    <div class="sys-item"><div class="sys-lbl">Bluetooth LE</div><div class="sys-val" id="sys-ble">--</div></div>
    <div class="sys-item sys-wide"><div class="sys-lbl">Wireless</div><div class="sys-val" id="sys-wireless">--</div></div>
    <div class="sys-item sys-wide"><div class="sys-lbl">MAC / Firmware</div><div class="sys-val" id="sys-fw">--</div></div>
  </div>
</div>

<div class="card can-debug-panel">
  <div class="card-hdr">
    <div class="card-title">Plugins <span class="title-help" onclick="return toggleHelp(this,event)" data-help-target="plg-info" title="Install and manage JSON plugins that modify CAN messages in real time.">?</span></div>
    <div class="card-meta" id="plg-count">0 installed</div>
  </div>

  <div id="plg-info" class="info-box" style="display:none;margin-bottom:12px">
    Plugins are JSON rules that modify CAN messages in real time. Install via URL, file upload or paste.
    <div style="margin-top:6px"><a href="https://ev-open-can-tools.github.io/ev-open-can-tools/docs/plugins.html" target="_blank" rel="noopener" style="color:var(--acc);text-decoration:none">Documentation &amp; examples &rarr;</a></div>
  </div>

  <div style="margin-bottom:14px">
    <div class="setting-name" style="margin-bottom:8px">Install Plugin <span class="title-help" onclick="return toggleHelp(this,event)" data-help-target="plg-info" title="Install a plugin from a URL or uploaded JSON file.">?</span></div>
    <div style="font-size:11px;color:var(--tx3);margin-bottom:8px" id="plg-limit">Maximum plugins: --</div>
    <div style="display:flex;gap:6px;margin-bottom:8px">
      <input class="sniff-input" id="plg-url" placeholder="Plugin JSON URL (https://...)" style="flex:1">
      <button class="sniff-btn" onclick="installPlugin()">Install</button>
    </div>
    <div style="display:flex;gap:8px;align-items:center;margin-bottom:8px">
      <input type="file" id="plg-file" accept=".json" onchange="uploadPlugin(this.files[0])" style="display:none">
      <button class="sniff-btn" onclick="$('plg-file').click()">Upload .json</button>
      <span style="font-size:11px;color:var(--tx3)" id="plg-status"></span>
    </div>
    <div class="setting-name" style="margin-bottom:6px">Paste JSON (offline) <span class="title-help" onclick="return toggleHelp(this,event)" title="Paste a full plugin JSON document directly into the editor below.">?</span></div>
    <textarea id="plg-paste" placeholder='{"name":"...","version":"1.0","rules":[...]}' style="width:100%;height:80px;resize:vertical;background:var(--bg2);color:var(--tx);border:1px solid var(--bd);border-radius:6px;padding:8px;font-family:monospace;font-size:11px;box-sizing:border-box;margin-bottom:6px"></textarea>
    <button class="sniff-btn" onclick="pastePlugin()">Install from JSON</button>
  </div>

  <div id="plg-conflicts" style="display:none;margin-bottom:10px"></div>
  <div id="plg-gtw-status" style="display:none;margin-bottom:10px"></div>

  <div class="subsec" data-subkey="plugins-replay" style="margin-bottom:12px">
    <div class="subsec-head">
      <div class="subsec-title">Plugin Repeat Count <span class="title-help" onclick="return toggleHelp(this,event)" title="Set how many modified GTW 2047 plugin frames are sent immediately per observed frame.">?</span></div>
      <div class="subsec-meta" id="plugin-replay-meta">1x</div>
    </div>
    <div class="subsec-body">
      <div class="setting-row" style="padding-top:0">
        <div class="setting-info">
          <div class="setting-name">GTW 2047 Replay Count</div>
          <div class="setting-desc">Modified GTW_autopilot frames sent per observed 0x7FF frame</div>
        </div>
        <input class="sniff-input" id="plugin-replay" type="number" min="1" max="20" value="1" style="width:72px;text-align:right">
        <button class="sniff-btn" onclick="savePluginReplay()">Save</button>
      </div>
      <div style="font-size:11px;color:var(--tx3);margin-top:6px" id="plugin-replay-status"></div>
    </div>
  </div>

  <div style="padding-top:12px;border-top:1px solid var(--bd)" id="plg-list">
    <div style="font-size:12px;color:var(--tx3);text-align:center;padding:12px">No plugins installed</div>
  </div>
</div>

<div class="card can-debug-panel">
  <div class="card-hdr">
    <div class="card-title">Plugin Editor <span class="title-help" onclick="return toggleHelp(this,event)" data-help-target="pe-info" title="Build, edit and test plugin rules without writing JSON by hand.">?</span></div>
    <div class="card-meta" id="pe-count">0 rules</div>
  </div>
  <div id="pe-info" class="info-box" style="display:none">
    Build or edit a plugin via form &mdash; no JSON writing needed. Load an installed plugin into the editor, change rules, then reinstall it. You can also send a temporary test frame for one rule before installing.
  </div>
  <div style="display:grid;grid-template-columns:minmax(0,1fr) minmax(0,1fr) 90px;gap:6px;margin-bottom:10px">
    <input class="sniff-input" id="pe-name" placeholder="Plugin name" maxlength="31" oninput="peRenderPreview()">
    <input class="sniff-input" id="pe-author" placeholder="Author (optional)" oninput="peRenderPreview()">
    <input class="sniff-input" id="pe-version" placeholder="Version" value="1.0" oninput="peRenderPreview()">
  </div>
  <div class="subsec" data-subkey="plugin-editor-quick-rule">
    <div class="subsec-head">
      <div class="subsec-title">Quick Rule <span class="title-help" onclick="return toggleHelp(this,event)" title="Create one plugin rule quickly from a shorthand CAN line.">?</span></div>
      <div class="subsec-meta">Fast builder</div>
    </div>
    <div class="subsec-body">
      <div class="info-box">
        <div style="font-size:11px;color:var(--tx3);line-height:1.5;margin-bottom:8px">
          Paste a shorthand line like <span style="font-family:monospace">0x7FF mux=2 byte[5] = 0x4C</span> to create one rule directly.
        </div>
        <div style="display:flex;gap:6px;flex-wrap:wrap">
          <input class="sniff-input" id="pe-shortcut" placeholder="0x7FF mux=2 byte[5] = 0x4C (bit 2 flipped -> tier 3 SELF_DRIVING)" onkeydown="if(event.key==='Enter'){event.preventDefault();peAddRuleFromShortcut()}" style="flex:1">
          <button class="sniff-btn" onclick="peAddRuleFromShortcut()">Add Shortcut</button>
        </div>
      </div>
    </div>
  </div>
  <div id="pe-rules"></div>
  <button class="sniff-btn" onclick="peAddRule()" style="margin-top:6px">+ Add Rule</button>
  <details style="margin-top:10px">
    <summary style="font-size:11px;color:var(--acc);cursor:pointer;user-select:none">JSON Preview</summary>
    <pre id="pe-preview" style="max-height:200px;overflow:auto;background:var(--bg2);border:1px solid var(--bd);border-radius:6px;padding:8px;font-size:11px;color:var(--tx2);margin-top:6px;white-space:pre-wrap;word-break:break-all"></pre>
  </details>
  <div class="subsec" data-subkey="plugin-editor-rule-test">
    <div class="subsec-head">
      <div class="subsec-title">Rule Test <span class="title-help" onclick="return toggleHelp(this,event)" title="Preview one rule on a live CAN frame, then inject the modified frame.">?</span></div>
      <div class="subsec-meta">Live frame preview</div>
    </div>
    <div class="subsec-body">
      <div style="font-size:11px;color:var(--tx3);line-height:1.5;margin-bottom:8px">
        Choose one rule from the editor. The dashboard waits for the next matching CAN frame, applies that rule to the live frame, then injects it the number of times you set below, spaced by the delay in milliseconds.
      </div>
      <div style="display:grid;grid-template-columns:minmax(0,1fr) 130px 120px;gap:6px;margin-bottom:6px;align-items:end">
        <select class="sniff-input" id="pe-test-rule" onchange="peUpdateTestPreview()"></select>
        <label style="display:block">
          <div style="font-size:11px;color:var(--tx2);font-weight:600;margin:0 0 4px 2px">Amount of times</div>
          <input class="sniff-input" id="pe-test-count" type="number" min="1" max="200" placeholder="1" title="Amount of times to inject" onchange="peUpdateTestPreview()">
        </label>
        <label style="display:block">
          <div style="font-size:11px;color:var(--tx2);font-weight:600;margin:0 0 4px 2px">Interval (ms)</div>
          <input class="sniff-input" id="pe-test-interval" type="number" min="10" max="5000" placeholder="100" title="Milliseconds between injected frames" onchange="peUpdateTestPreview()">
        </label>
      </div>
      <pre id="pe-test-preview" style="min-height:54px;overflow:auto;background:var(--bg2);border:1px solid var(--bd);border-radius:6px;padding:8px;font-size:11px;color:var(--tx2);white-space:pre-wrap;word-break:break-word">Add a rule to preview a test frame.</pre>
      <div style="display:flex;gap:6px;align-items:center;margin-top:8px;flex-wrap:wrap">
        <button class="sniff-btn" onclick="peStartTest()">Start Test</button>
        <button class="sniff-btn" onclick="peStopTest()">Stop Test</button>
        <span id="pe-test-status" style="font-size:11px;color:var(--tx3)">Idle</span>
      </div>
    </div>
  </div>
  <div style="display:flex;gap:6px;margin-top:10px">
    <button class="sniff-btn" onclick="peInstall()">Install</button>
    <button class="sniff-btn" onclick="peDownload()">Download JSON</button>
    <button class="sniff-btn" onclick="peReset()">Reset</button>
  </div>
  <div id="pe-status" style="font-size:11px;margin-top:6px;color:var(--tx3)"></div>
</div>



<div class="card">
  <div class="card-hdr">
    <div class="card-title">Configuration <span class="title-help" onclick="return toggleHelp(this,event)" title="Device settings for hardware mode, WiFi, CAN pins, logging and backup.">?</span></div>
    <div class="card-meta">Device settings</div>
  </div>

  <div class="subsec" data-subkey="config-hardware">
    <div class="subsec-head">
      <div class="subsec-title">Hardware <span class="title-help" onclick="return toggleHelp(this,event)" title="Select the autopilot hardware generation and matching speed profile set.">?</span></div>
      <div class="subsec-meta">Autopilot generation</div>
    </div>
    <div class="subsec-body">
      <div class="hw-seg" id="hw-seg">
        <button class="hw-btn" data-v="0" onclick="setHW(0)">Legacy</button>
        <button class="hw-btn active" data-v="1" onclick="setHW(1)">HW3</button>
        <button class="hw-btn" data-v="2" onclick="setHW(2)">HW4</button>
      </div>
      <div class="profile-wrap">
        <div class="profile-label">Profile</div>
        <div class="profile-group" id="sp3-group">
          <div class="hw-seg" id="sp3-seg">
            <button class="hw-btn" data-v="-1" onclick="setProfileAuto()">Auto</button>
            <button class="hw-btn" data-v="0" onclick="setProfile(0)">Chill</button>
            <button class="hw-btn" data-v="1" onclick="setProfile(1)">Normal</button>
            <button class="hw-btn" data-v="2" onclick="setProfile(2)">Hurry</button>
          </div>
        </div>
        <div class="profile-group hidden" id="sp4-group">
          <div class="hw-seg" id="sp4-seg">
            <button class="hw-btn" data-v="-1" onclick="setProfileAuto()">Auto</button>
            <button class="hw-btn" data-v="0" onclick="setProfile(0)">Chill</button>
            <button class="hw-btn" data-v="1" onclick="setProfile(1)">Normal</button>
            <button class="hw-btn" data-v="2" onclick="setProfile(2)">Hurry</button>
            <button class="hw-btn" data-v="3" onclick="setProfile(3)">Max</button>
            <button class="hw-btn" data-v="4" onclick="setProfile(4)">Sloth</button>
          </div>
        </div>
        <div class="profile-note" id="profile-note">Available profiles depend on the selected hardware.</div>
      </div>
    </div>
  </div>

  <div class="subsec" data-subkey="config-force-activate">
    <div class="subsec-head">
      <div class="subsec-title">Force FSD Activate <span class="title-help" onclick="return toggleHelp(this,event)" title="When enabled, CAN Injection ignores the vehicle UI FSD trigger bit and treats FSD as requested. Plugin injection still follows AP Injection Gate.">?</span></div>
      <div class="subsec-meta" id="force-meta">Off</div>
    </div>
    <div class="subsec-body">
      <div class="setting-row" style="padding-top:0">
        <div class="setting-info">
          <div class="setting-name">Treat FSD as requested</div>
          <div class="setting-desc">Applies while CAN Injection is active; plugins still follow AP After-Start Gate</div>
        </div>
        <label class="tgl"><input type="checkbox" id="force-tgl" onchange="saveForceActivate()"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
      </div>
      <div style="font-size:11px;color:var(--tx3);margin-top:6px" id="force-status"></div>
    </div>
  </div>

  <div class="subsec" id="hw3-speed-section" data-subkey="config-hw3-speed">
    <div class="subsec-head">
      <div class="subsec-title">HW3 Custom Speed Limit <span class="title-help" onclick="return toggleHelp(this,event)" title="Override AP fused speed limit by writing a synthetic offset into 1021 mux 2. Custom uses the per-bucket table; High-speed uses target km/h values above 80 km/h.">?</span></div>
      <div class="subsec-meta" id="hw3-speed-meta">Off</div>
    </div>
    <div class="subsec-body">
      <div class="setting-row" style="padding-top:0">
        <div class="setting-info">
          <div class="setting-name">Custom table</div>
          <div class="setting-desc">30/40/50/60/70 km/h buckets</div>
        </div>
        <label class="tgl"><input type="checkbox" id="hw3-cust-tgl" onchange="saveHw3Speed()"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
      </div>
      <div style="display:grid;grid-template-columns:repeat(5,1fr);gap:6px;margin-top:8px">
        <div class="stat" style="padding:6px"><div class="stat-lbl">30→</div><input class="sniff-input" id="hw3-ct-0" type="number" min="0" max="160" value="60" onchange="saveHw3Speed()" style="width:100%;text-align:right"></div>
        <div class="stat" style="padding:6px"><div class="stat-lbl">40→</div><input class="sniff-input" id="hw3-ct-1" type="number" min="0" max="160" value="60" onchange="saveHw3Speed()" style="width:100%;text-align:right"></div>
        <div class="stat" style="padding:6px"><div class="stat-lbl">50→</div><input class="sniff-input" id="hw3-ct-2" type="number" min="0" max="160" value="65" onchange="saveHw3Speed()" style="width:100%;text-align:right"></div>
        <div class="stat" style="padding:6px"><div class="stat-lbl">60→</div><input class="sniff-input" id="hw3-ct-3" type="number" min="0" max="160" value="70" onchange="saveHw3Speed()" style="width:100%;text-align:right"></div>
        <div class="stat" style="padding:6px"><div class="stat-lbl">70→</div><input class="sniff-input" id="hw3-ct-4" type="number" min="0" max="160" value="80" onchange="saveHw3Speed()" style="width:100%;text-align:right"></div>
      </div>
      <div class="setting-row">
        <div class="setting-info">
          <div class="setting-name">High-speed boost (≥80 km/h)</div>
          <div class="setting-desc">80/100/120 km/h target speeds</div>
        </div>
        <label class="tgl"><input type="checkbox" id="hw3-hs-tgl" onchange="saveHw3Speed()"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
      </div>
      <div style="display:grid;grid-template-columns:repeat(3,1fr);gap:6px;margin-top:8px">
        <div class="stat" style="padding:6px"><div class="stat-lbl">80→</div><input class="sniff-input" id="hw3-hs-0" type="number" min="0" max="200" value="90" onchange="saveHw3Speed()" style="width:100%;text-align:right"></div>
        <div class="stat" style="padding:6px"><div class="stat-lbl">100→</div><input class="sniff-input" id="hw3-hs-1" type="number" min="0" max="200" value="110" onchange="saveHw3Speed()" style="width:100%;text-align:right"></div>
        <div class="stat" style="padding:6px"><div class="stat-lbl">120→</div><input class="sniff-input" id="hw3-hs-2" type="number" min="0" max="200" value="130" onchange="saveHw3Speed()" style="width:100%;text-align:right"></div>
      </div>
      <div class="setting-row">
        <div class="setting-info">
          <div class="setting-name">Wire encoding</div>
          <div class="setting-desc">PCT4=current, KPH5=legacy fleets</div>
        </div>
        <select class="sniff-input" id="hw3-enc" onchange="saveHw3Speed()" style="width:96px;flex:0 0 auto">
          <option value="1">PCT4</option>
          <option value="0">KPH5</option>
        </select>
      </div>
      <div style="display:grid;grid-template-columns:repeat(3,1fr);gap:6px;margin-top:10px">
        <div class="stat" style="padding:8px"><div class="stat-lbl">Fused</div><div class="stat-val" id="hw3-fused">0</div></div>
        <div class="stat" style="padding:8px"><div class="stat-lbl">Stock limit offset</div><div class="stat-val" id="hw3-stock-off">0</div></div>
        <div class="stat" style="padding:8px"><div class="stat-lbl">Write raw</div><div class="stat-val" id="hw3-tgt-raw">0</div></div>
      </div>
      <div style="font-size:11px;color:var(--tx3);margin-top:6px" id="hw3-speed-status"></div>
    </div>
  </div>

  <div class="subsec" id="legacy-mpp-section" data-subkey="config-legacy-mpp">
    <div class="subsec-head">
      <div class="subsec-title">Legacy Custom Speed Limit <span class="title-help" onclick="return toggleHelp(this,event)" title="Raise UI_mppSpeedLimit on CAN 760 byte 6 to a target km/h based on what the gateway is currently sending. Same bucket layout as HW3. Only writes when target is higher than current — never lowers.">?</span></div>
      <div class="subsec-meta" id="legacy-mpp-meta">Off</div>
    </div>
    <div class="subsec-body">
      <div class="setting-row" style="padding-top:0">
        <div class="setting-info">
          <div class="setting-name">Master enable</div>
          <div class="setting-desc">Allow this module to write to UI_mppSpeedLimit</div>
        </div>
        <label class="tgl"><input type="checkbox" id="legacy-mpp-tgl" onchange="saveLegacyMpp()"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
      </div>
      <div class="setting-row">
        <div class="setting-info">
          <div class="setting-name">Custom table</div>
          <div class="setting-desc">30/40/50/60/70 km/h buckets</div>
        </div>
        <label class="tgl"><input type="checkbox" id="legacy-mpp-cust-tgl" onchange="saveLegacyMpp()"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
      </div>
      <div style="display:grid;grid-template-columns:repeat(5,1fr);gap:6px;margin-top:8px">
        <div class="stat" style="padding:6px"><div class="stat-lbl">30→</div><input class="sniff-input" id="legacy-mpp-ct-0" type="number" min="0" max="155" value="60" onchange="saveLegacyMpp()" style="width:100%;text-align:right"></div>
        <div class="stat" style="padding:6px"><div class="stat-lbl">40→</div><input class="sniff-input" id="legacy-mpp-ct-1" type="number" min="0" max="155" value="60" onchange="saveLegacyMpp()" style="width:100%;text-align:right"></div>
        <div class="stat" style="padding:6px"><div class="stat-lbl">50→</div><input class="sniff-input" id="legacy-mpp-ct-2" type="number" min="0" max="155" value="65" onchange="saveLegacyMpp()" style="width:100%;text-align:right"></div>
        <div class="stat" style="padding:6px"><div class="stat-lbl">60→</div><input class="sniff-input" id="legacy-mpp-ct-3" type="number" min="0" max="155" value="70" onchange="saveLegacyMpp()" style="width:100%;text-align:right"></div>
        <div class="stat" style="padding:6px"><div class="stat-lbl">70→</div><input class="sniff-input" id="legacy-mpp-ct-4" type="number" min="0" max="155" value="80" onchange="saveLegacyMpp()" style="width:100%;text-align:right"></div>
      </div>
      <div class="setting-row">
        <div class="setting-info">
          <div class="setting-name">High-speed boost (≥80 km/h)</div>
          <div class="setting-desc">80/100/120 km/h target speeds</div>
        </div>
        <label class="tgl"><input type="checkbox" id="legacy-mpp-hs-tgl" onchange="saveLegacyMpp()"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
      </div>
      <div style="display:grid;grid-template-columns:repeat(3,1fr);gap:6px;margin-top:8px">
        <div class="stat" style="padding:6px"><div class="stat-lbl">80→</div><input class="sniff-input" id="legacy-mpp-hs-0" type="number" min="0" max="155" value="90" onchange="saveLegacyMpp()" style="width:100%;text-align:right"></div>
        <div class="stat" style="padding:6px"><div class="stat-lbl">100→</div><input class="sniff-input" id="legacy-mpp-hs-1" type="number" min="0" max="155" value="110" onchange="saveLegacyMpp()" style="width:100%;text-align:right"></div>
        <div class="stat" style="padding:6px"><div class="stat-lbl">120→</div><input class="sniff-input" id="legacy-mpp-hs-2" type="number" min="0" max="155" value="130" onchange="saveLegacyMpp()" style="width:100%;text-align:right"></div>
      </div>
      <div style="display:grid;grid-template-columns:repeat(2,1fr);gap:6px;margin-top:10px">
        <div class="stat" style="padding:8px"><div class="stat-lbl">Bus raw</div><div class="stat-val" id="legacy-mpp-bus-raw">0</div></div>
        <div class="stat" style="padding:8px"><div class="stat-lbl">Sent raw</div><div class="stat-val" id="legacy-mpp-sent-raw">0</div></div>
      </div>
      <div style="font-size:11px;color:var(--tx3);margin-top:6px" id="legacy-mpp-status"></div>
    </div>
  </div>

  <div class="subsec" id="hw3-slew-section" data-subkey="config-hw3-slew">
    <div class="subsec-head">
      <div class="subsec-title">HW3 Offset Slew <span class="title-help" onclick="return toggleHelp(this,event)" title="Limits downward HW3 mux 2 offset changes sent by enabled dashboard plugins.">?</span></div>
      <div class="subsec-meta" id="hw3-slew-meta">Off</div>
    </div>
    <div class="subsec-body">
      <div class="setting-row" style="padding-top:0">
        <div class="setting-info">
          <div class="setting-name">Ramp-down limiter</div>
          <div class="setting-desc">Opt-in only; increases still pass immediately</div>
        </div>
        <label class="tgl"><input type="checkbox" id="hw3-slew-tgl" onchange="saveHw3Slew()"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
      </div>
      <div class="setting-row">
        <div class="setting-info">
          <div class="setting-name">Offset drop rate</div>
          <div class="setting-desc" id="hw3-slew-rate-hint">5%/s</div>
        </div>
        <input class="sniff-input" id="hw3-slew-rate" type="number" min="1" max="25" value="5" onchange="saveHw3Slew()" style="width:72px;text-align:right;flex:0 0 auto">
      </div>
      <div style="display:grid;grid-template-columns:repeat(3,1fr);gap:6px;margin-top:10px">
        <div class="stat" style="padding:8px"><div class="stat-lbl">Target</div><div class="stat-val" id="hw3-slew-target">0</div></div>
        <div class="stat" style="padding:8px"><div class="stat-lbl">Last</div><div class="stat-val" id="hw3-slew-last">0</div></div>
        <div class="stat" style="padding:8px"><div class="stat-lbl">Capped</div><div class="stat-val" id="hw3-slew-count">0</div></div>
      </div>
      <div style="font-size:11px;color:var(--tx3);margin-top:6px" id="hw3-slew-status"></div>
    </div>
  </div>

  <div class="subsec" data-subkey="config-ap-injection-gate">
    <div class="subsec-head">
      <div class="subsec-title">AP After-Start Gate <span class="title-help" onclick="return toggleHelp(this,event)" title="When enabled, plugin injection waits for AP, Park or Summon. Built-in Force FSD Activate is not gated by this switch.">?</span></div>
      <div class="subsec-meta" id="ap-gate-meta">Off</div>
    </div>
    <div class="subsec-body">
      <div class="setting-row" style="padding-top:0">
        <div class="setting-info">
          <div class="setting-name">Start after AP</div>
          <div class="setting-desc">Hold plugin injection until AP or NoA is active</div>
        </div>
        <label class="tgl"><input type="checkbox" id="ap-gate-tgl" onchange="saveApGate()"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
      </div>
      <div style="font-size:11px;color:var(--tx3);margin-top:6px" id="ap-gate-status"></div>
    </div>
  </div>

  <div class="subsec" data-subkey="config-wifi-hotspot">
    <div class="subsec-head">
      <div class="subsec-title">WiFi Hotspot <span class="title-help" onclick="return toggleHelp(this,event)" data-help-target="ap-info" title="Configure the device hotspot name, password and visibility. Saved in NVS.">?</span></div>
      <div class="subsec-meta"><span id="ap-stored" style="margin-right:8px"></span><span id="ap-clients">0 clients</span></div>
    </div>
    <div class="subsec-body">
      <div id="ap-info" class="info-box" style="display:none">
        Stored in NVS (non-volatile storage). The SSID and password survive firmware updates and reboots. Only a full factory erase via USB clears them.
      </div>
      <div class="setting-desc" style="margin-bottom:8px">Change the WiFi hotspot name and password</div>
      <div style="display:flex;gap:6px;margin-bottom:6px">
        <input class="sniff-input" id="ap-ssid" placeholder="Hotspot Name" style="flex:1">
        <input class="sniff-input" id="ap-pass" placeholder="New Password (min 8)" type="password" style="flex:1">
      </div>
      <div class="setting-row" style="padding:8px 0">
        <div class="setting-info">
          <div class="setting-name">Hide SSID</div>
          <div class="setting-desc">Don't broadcast the hotspot name &mdash; clients must enter it manually</div>
        </div>
        <label class="tgl"><input type="checkbox" id="ap-hidden"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
      </div>
      <div style="display:flex;gap:6px;align-items:center">
        <button class="sniff-btn" onclick="saveAP()">Save</button>
        <span style="font-size:11px;color:var(--tx3)" id="ap-status"></span>
      </div>
      <div style="font-size:10px;color:var(--tx3);margin-top:6px">Changes take effect after reboot. Leave password empty to keep current.</div>
    </div>
  </div>

  <div class="subsec" data-subkey="config-wifi-internet">
    <div class="subsec-head">
      <div class="subsec-title">WiFi Internet <span class="title-help" onclick="return toggleHelp(this,event)" title="Up to 4 saved networks. The device tries each in turn until one connects.">?</span></div>
      <div class="subsec-meta"><span id="wifi-status">Not configured</span></div>
    </div>
    <div class="subsec-body">
      <div class="setting-desc" style="margin-bottom:8px">Save up to 4 networks (e.g. home + phone hotspot). Device tries each in turn. Stored in NVS &mdash; survives firmware updates.</div>
      <div id="wifi-saved-list" style="margin-bottom:8px"></div>
      <div id="wifi-add-wrap">
        <div class="setting-desc" style="margin-bottom:6px"><b>Add network</b> <span id="wifi-slot-count" style="color:var(--tx3)">(0/4)</span></div>
        <div style="display:flex;gap:6px;margin-bottom:6px">
          <input class="sniff-input" id="wifi-ssid" placeholder="WiFi SSID" style="flex:1">
          <button class="sniff-btn" onclick="scanWifi()" id="scan-btn">Scan</button>
        </div>
        <div id="wifi-nets" style="display:none;margin-bottom:6px;max-height:140px;overflow-y:auto;border:1px solid var(--bd);border-radius:6px;background:var(--bg2)"></div>
        <div style="display:flex;gap:6px;margin-bottom:6px">
          <input class="sniff-input" id="wifi-pass" placeholder="Password" type="password" style="flex:1">
          <button class="sniff-btn" onclick="saveWifi()" id="wifi-save-btn">Save &amp; Connect</button>
        </div>
        <details style="margin-top:4px">
          <summary style="font-size:11px;color:var(--acc);cursor:pointer;user-select:none">Static IP (optional) <span class="title-help" onclick="return toggleHelp(this,event)" title="Set a fixed IP configuration instead of using DHCP.">?</span></summary>
          <div style="margin-top:6px">
            <label style="font-size:11px;color:var(--tx3);display:flex;align-items:center;gap:6px;margin-bottom:6px">
              <input type="checkbox" id="wifi-static" onchange="toggleStaticIP()"> Use static IP
            </label>
            <div id="static-fields" style="display:none">
              <div style="display:grid;grid-template-columns:1fr 1fr;gap:4px">
                <input class="sniff-input" id="wifi-ip" placeholder="IP (e.g. 192.168.1.100)">
                <input class="sniff-input" id="wifi-gw" placeholder="Gateway (e.g. 192.168.1.1)">
                <input class="sniff-input" id="wifi-mask" placeholder="Mask (255.255.255.0)" value="255.255.255.0">
                <input class="sniff-input" id="wifi-dns" placeholder="DNS (e.g. 8.8.8.8)">
              </div>
            </div>
          </div>
        </details>
        <input type="hidden" id="wifi-edit-idx" value="-1">
      </div>
    </div>
  </div>

  <div class="subsec" data-subkey="config-gateway">
    <div class="subsec-head">
      <div class="subsec-title">STA-AP Gateway <span class="title-help" onclick="return toggleHelp(this,event)" title="Routes hotspot clients through the configured WiFi Internet uplink, with DNS filtering.">?</span></div>
      <div class="subsec-meta"><span id="gw-status">Gateway status unavailable</span></div>
    </div>
    <div class="subsec-body">
      <div class="setting-row" style="padding:8px 0">
        <div class="setting-info">
          <div class="setting-name">Gateway</div>
          <div class="setting-desc">Enable STA-AP NAT routing for hotspot clients when WiFi Internet is connected</div>
        </div>
        <label class="tgl"><input type="checkbox" id="gw-enabled"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
      </div>
      <div style="display:grid;grid-template-columns:1fr 1fr;gap:6px;margin-bottom:8px">
        <button class="sniff-btn gateway-mode-btn" id="gw-mode-black" onclick="setGatewayMode(0,true)">Blacklist Mode</button>
        <button class="sniff-btn gateway-mode-btn" id="gw-mode-white" onclick="setGatewayMode(1,true)">Whitelist Mode</button>
      </div>
      <div id="gw-mode-hint" style="font-size:11px;color:var(--tx3);margin:-2px 0 8px"></div>
      <label style="font-size:11px;color:var(--tx3);display:flex;align-items:center;gap:6px;margin-bottom:8px">
        <input type="checkbox" id="gw-strict"> Strict DNS mode
      </label>
      <div style="margin-bottom:10px">
        <div style="font-size:12px;font-weight:600;color:var(--tx2);margin-bottom:4px">Blacklist</div>
        <textarea class="sniff-input" id="gw-blacklist" rows="5" placeholder="Blocked domains, one per line" style="width:100%;resize:vertical"></textarea>
      </div>
      <div style="margin-bottom:10px">
        <div style="font-size:12px;font-weight:600;color:var(--tx2);margin-bottom:4px">Whitelist</div>
        <textarea class="sniff-input" id="gw-whitelist" rows="5" placeholder="Allowed domains, one per line" style="width:100%;resize:vertical"></textarea>
      </div>
      <div style="margin-bottom:10px">
        <div style="display:flex;align-items:center;justify-content:space-between;margin-bottom:4px">
          <div style="font-size:12px;font-weight:600;color:var(--tx2)">Filter List</div>
          <div style="display:flex;gap:6px">
            <button class="sniff-btn" onclick="loadGatewayBlocked()" style="padding:3px 8px;font-size:10px">Refresh</button>
            <button class="sniff-btn" onclick="clearGatewayBlocked()" style="padding:3px 8px;font-size:10px">Clear</button>
          </div>
        </div>
        <div id="gw-blocked-list" class="dns-modal-list" style="margin-top:0;max-height:240px"></div>
        <div id="gw-blocked-summary" style="font-size:10px;color:var(--tx3);margin-top:4px"></div>
        <div id="gw-blocked-msg" style="font-size:10px;color:var(--tx3);margin-top:2px"></div>
      </div>
      <div style="display:flex;gap:6px;margin-bottom:6px">
        <input class="sniff-input" id="gw-test-domain" placeholder="Test domain">
        <button class="sniff-btn" onclick="testGatewayDns()">Test DNS</button>
      </div>
      <div id="gw-test-result" style="font-size:11px;color:var(--tx3);margin-bottom:8px"></div>
      <div style="display:flex;gap:6px;align-items:center;flex-wrap:wrap">
        <button class="sniff-btn" onclick="saveGatewayDns()">Save DNS</button>
        <span style="font-size:11px;color:var(--tx3)" id="gw-msg"></span>
        <span id="gw-list-counts" style="font-size:11px;color:var(--tx3);margin-left:auto"></span>
      </div>
      <div id="gw-strict-panel" style="display:none;margin-top:10px;padding:8px;border:1px solid var(--bd);border-radius:8px;background:var(--bg2)">
        <div style="display:flex;justify-content:space-between;align-items:center;margin-bottom:6px">
          <span style="font-weight:600;color:var(--tx2)">Strict Mode IPs</span>
          <span id="gw-strict-stats" style="font-size:11px;color:var(--tx3)"></span>
        </div>
        <div style="display:flex;gap:6px;margin-bottom:6px">
          <button class="sniff-btn" onclick="loadGatewayBlockedIps()">Refresh Blocked IPs</button>
          <button class="sniff-btn" onclick="clearGatewayBlockedIps()">Clear Blocked IPs</button>
        </div>
        <div id="gw-blocked-ips" style="font-size:11px;color:var(--tx3);max-height:160px;overflow:auto"></div>
      </div>
    </div>
  </div>

  <div class="subsec can-debug-panel" data-subkey="config-can-pins">
    <div class="subsec-head">
      <div class="subsec-title">CAN Pins <span class="title-help" onclick="return toggleHelp(this,event)" title="Set the ESP32 GPIO pins used for the CAN transceiver. Wrong values can disable CAN.">?</span></div>
      <div class="subsec-meta" id="can-pins-status">default</div>
    </div>
    <div class="subsec-body">
      <div style="display:flex;gap:6px;align-items:center">
        <input class="sniff-input" id="can-tx" type="number" min="0" max="39" placeholder="TX GPIO" style="flex:1">
        <input class="sniff-input" id="can-rx" type="number" min="0" max="39" placeholder="RX GPIO" style="flex:1">
        <button class="sniff-btn" onclick="saveCanPins()">Save</button>
      </div>
      <div style="font-size:11px;color:var(--tx3);margin-top:6px" id="can-pins-hint">Reboot required after change</div>
    </div>
  </div>

  <div class="subsec can-debug-panel" data-subkey="config-dashboard-log" style="margin-top:14px">
    <div class="subsec-head">
      <div class="subsec-title">Debug Log <span class="title-help" onclick="return toggleHelp(this,event)" title="Shows recent WebUI and firmware log lines. This is debug logging output, not the CAN sniffer.">?</span></div>
      <div class="subsec-meta">Recent debug output</div>
    </div>
    <div class="subsec-body">
      <div class="setting-row" style="padding-top:0">
        <div class="setting-info">
          <div class="setting-name">Debug logging <span class="title-help" onclick="return toggleHelp(this,event)" title="Turns WebUI debug log output on or off.">?</span></div>
          <div class="setting-desc">Toggle WebUI and firmware debug output</div>
        </div>
        <label class="tgl"><input type="checkbox" id="tgl-eprn" checked onchange="pushLogging()">
          <div class="tgl-track"><div class="tgl-thumb"></div></div></label>
      </div>
      <div class="log-box" id="log">Waiting...</div>
    </div>
  </div>
  <div class="setting-row" style="margin-top:14px;padding-top:12px;border-top:1px solid var(--bd)">
    <div class="setting-info">
      <div class="setting-name">Settings Backup <span class="title-help" onclick="return toggleHelp(this,event)" data-help-target="backup-info" title="Export or restore saved device settings as JSON.">?</span></div>
      <div class="setting-desc">Export and import device settings</div>
    </div>
    <button class="sniff-btn" onclick="exportSettings()">Download</button>
    <button class="sniff-btn" onclick="document.getElementById('backup-file').click()">Upload &amp; Restore</button>
    <input type="file" id="backup-file" accept=".json,application/json" style="display:none" onchange="importSettings(event)">
    <span style="font-size:11px;color:var(--tx3)" id="backup-status"></span>
  </div>
  <div class="setting-row can-debug-panel" style="padding-top:12px;border-top:1px solid var(--bd)">
    <div class="setting-info">
      <div class="setting-name">Support <span class="title-help" onclick="return toggleHelp(this,event)" title="Collect a support summary and open a GitHub issue with the details prefilled.">?</span></div>
      <div class="setting-desc">Copy a status summary before opening a GitHub issue</div>
    </div>
    <button class="sniff-btn" onclick="openSupport()">Open</button>
  </div>
  <div id="backup-info" class="info-box" style="display:none">
    Exports AP credentials, WiFi Internet, CAN pins and beta channel as JSON. Useful before a full re-flash or when migrating to another device. <b>Passwords are included in clear text</b> &mdash; keep the file safe.
  </div>
</div>

<div class="card can-debug-panel">
  <div class="card-hdr">
    <div class="card-title">Firmware Update <span class="title-help" onclick="return toggleHelp(this,event)" title="Check for updates, enable beta builds and upload firmware manually.">?</span></div>
    <div class="card-meta" id="fw-ver">Version info</div>
  </div>
  <div style="margin-bottom:10px">
    <div class="setting-row">
      <div class="setting-info">
        <div class="setting-name">Beta Channel <span class="title-help" onclick="return toggleHelp(this,event)" title="Shows pre-release firmware versions when available.">?</span></div>
        <div class="setting-desc">Include pre-release / beta firmware versions</div>
      </div>
      <label class="tgl"><input type="checkbox" id="beta-tgl" onchange="toggleBeta()"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
    </div>
    <div class="setting-row">
      <div class="setting-info">
        <div class="setting-name">Auto-Update on Boot <span class="title-help" onclick="return toggleHelp(this,event)" title="Checks for firmware updates automatically shortly after WiFi connects.">?</span></div>
        <div class="setting-desc">Check and install updates automatically ~15 s after WiFi connects</div>
      </div>
      <label class="tgl"><input type="checkbox" id="auto-upd-tgl" onchange="toggleAutoUpdate()"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
    </div>
  </div>
  <div style="display:flex;gap:6px;align-items:center">
    <button class="sniff-btn" onclick="checkUpdate()" id="upd-check-btn">Check for Updates</button>
    <span style="font-size:11px;color:var(--tx3)" id="upd-status"></span>
  </div>
  <div id="upd-info" class="info-box" style="display:none;margin-top:10px">
    <div style="display:flex;justify-content:space-between;align-items:center">
      <div>
        <div style="font-size:13px;font-weight:600" id="upd-ver"></div>
        <div style="font-size:11px;color:var(--tx3)" id="upd-detail"></div>
      </div>
      <button class="sniff-btn" onclick="installUpdate()" id="upd-install-btn" style="background:var(--ok);color:#fff;border-color:var(--ok)">Install</button>
    </div>
  </div>

  <details id="manual-fw-upload" style="margin-top:14px;padding-top:12px;border-top:1px solid var(--bd)">
    <summary style="font-size:12px;color:var(--acc);cursor:pointer;user-select:none">Manual firmware upload (.bin) <span class="title-help" onclick="return toggleHelp(this,event)" title="Upload a local firmware .bin file directly to the device.">?</span></summary>
    <div style="margin-top:10px">
      <div class="ota-drop" id="ota-drop" onclick="$('ota-file').click()" ondragover="event.preventDefault();this.classList.add('drag')" ondragleave="this.classList.remove('drag')" ondrop="handleDrop(event)">
        <input type="file" id="ota-file" accept=".bin" onchange="fileSelected(this.files[0])">
        <div class="ota-icon">&#8679;</div>
        <div class="ota-text">Tap to select firmware .bin</div>
        <div class="ota-sub">Or drag and drop a file here</div>
      </div>
      <div class="ota-progress" id="ota-progress">
        <div class="ota-bar"><div class="ota-fill" id="ota-fill"></div></div>
        <div class="ota-status" id="ota-status">Uploading...</div>
      </div>
      <button class="ota-btn" id="ota-upload-btn" onclick="uploadFirmware()">Flash Firmware</button>
      <button class="sniff-btn" id="ota-reset-btn" onclick="resetOtaCredentials()" style="width:100%;margin-top:6px">Reset OTA Credentials</button>
      <div style="margin-top:10px;font-size:11px;color:var(--tx3);line-height:1.7">
        Build your .bin in PlatformIO: <span style="color:var(--acc);font-family:monospace">Ctrl+Alt+B</span><br>
        File is at: <span style="color:var(--acc);font-family:monospace">.pio/build/esp32_ext_mcp2515/firmware.bin</span>
      </div>
    </div>
  </details>
</div>
<div class="card can-debug-panel">
  <div class="card-hdr"><div class="card-title">CAN <span class="title-help" onclick="return toggleHelp(this,event)" title="Live CAN tools for sniffing, recording, controller status and checking the last injected write.">?</span></div><div class="card-meta">Sniffer, recorder and bus status</div></div>

  <div class="subsec" data-subkey="can-sniffer">
    <div class="subsec-head">
      <div class="subsec-title">CAN Sniffer <span class="title-help" onclick="return toggleHelp(this,event)" title="Shows the latest 30 CAN frames live. You can filter by ID or name, switch between wire IDs and DBC IDs, and pause the view.">?</span></div>
      <div class="subsec-meta" id="sniff-count">0 frames</div>
    </div>
    <div class="subsec-body">
      <div class="sniff-ctrl">
        <input class="sniff-input" id="sniff-filter" placeholder="Filter by ID or name" oninput="renderSniffer()">
        <button class="sniff-btn" id="sniff-id-btn" onclick="toggleSniffIdMode()">Wire IDs</button>
        <button class="sniff-btn" id="sniff-pause-btn" onclick="togglePause()">Pause</button>
      </div>
      <div class="sniff-box" id="sniffer">
        <div style="padding:20px;color:var(--tx3);text-align:center;font-size:12px">Waiting for CAN frames</div>
      </div>
    </div>
  </div>

  <div class="subsec" data-subkey="can-recorder">
    <div class="subsec-head">
      <div class="subsec-title">CAN Recorder <span class="title-help" onclick="return toggleHelp(this,event)" title="Records live CAN traffic up to the frame limit and lets you download it as a CSV file.">?</span></div>
      <div class="subsec-meta" id="rec-meta">Idle</div>
    </div>
    <div class="subsec-body">
      <div class="rec-bar"><div class="rec-fill" id="rec-fill"></div></div>
      <div class="rec-info">
        <span id="rec-count">0 / 2000 frames</span>
        <span id="rec-status">Ready</span>
      </div>
      <div class="btn-row">
        <button class="btn" id="rec-btn" onclick="toggleRec()">Start Recording</button>
        <a class="btn" id="rec-dl" href="/rec_download" download="can_recording.csv" style="display:none;text-align:center;text-decoration:none;padding:10px;border:1px solid var(--bd2);color:var(--tx2)">Download CSV</a>
      </div>
    </div>
  </div>

  <div class="subsec" data-subkey="can-controller">
    <div class="subsec-head">
      <div class="subsec-title">CAN Controller <span class="title-help" onclick="return toggleHelp(this,event)" title="Shows CAN controller health, error flags and the RX, TX and error counters per mux.">?</span></div>
      <div class="subsec-meta" style="display:flex;align-items:center;gap:8px">
        <button onclick="resetStats()" style="font-size:10px;padding:2px 8px;border:1px solid var(--bd2);border-radius:5px;background:transparent;color:var(--tx3);cursor:pointer;font-family:inherit">Reset</button>
      </div>
    </div>
    <div class="subsec-body">
      <div class="eflg-row" id="eflg-row"><span class="eflg-pill eflg-ok">OK</span></div>
      <table class="mux-tbl">
        <tr><th>Mux</th><th>RX</th><th>TX</th><th>Errors</th></tr>
        <tr><td>0</td><td id="m0rx">0</td><td id="m0tx">0</td><td id="m0err">0</td></tr>
        <tr><td>1</td><td id="m1rx">0</td><td id="m1tx">0</td><td id="m1err">0</td></tr>
        <tr><td>2</td><td id="m2rx">0</td><td id="m2tx">0</td><td id="m2err">0</td></tr>
      </table>
    </div>
  </div>

  <div class="subsec" data-subkey="can-last-write-check">
    <div class="subsec-head">
      <div class="subsec-title">Last Write Check <span class="title-help" onclick="return toggleHelp(this,event)" title="Compares the last injected frame with the latest bus frame that has the same CAN ID and mux. Helpful to spot overwrites, but not proof that a module accepted the change.">?</span></div>
    </div>
    <div class="subsec-body">
      <div class="probe-status v-dim" id="probe-status">No injected frame yet</div>
      <div class="probe-block">
        <div class="probe-label">Sent</div>
        <div class="probe-meta" id="probe-tx-meta">—</div>
        <div class="probe-hex" id="probe-tx">—</div>
      </div>
      <div class="probe-block">
        <div class="probe-label">Bus</div>
        <div class="probe-meta" id="probe-rx-meta">—</div>
        <div class="probe-hex" id="probe-rx">—</div>
      </div>
    </div>
  </div>
</div>

<div class="card" id="can-debug-card">
  <div class="card-hdr">
    <div class="card-title">CAN调试 <span class="title-help" onclick="return toggleHelp(this,event)" title="Enable debug panels: plugins, plugin editor, firmware update, debug log and live CAN tools.">?</span></div>
    <div class="card-meta" id="can-debug-meta">Off</div>
  </div>
  <div class="setting-row" style="padding-top:0">
    <div class="setting-info">
      <div class="setting-name">Enable CAN debug tools</div>
      <div class="setting-desc">Shows 2.5.2 debug panels and starts their WebUI polling only while enabled</div>
    </div>
    <label class="tgl"><input type="checkbox" id="can-debug-tgl" onchange="toggleCanDebug()"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>
  </div>
</div>

<div class="warn-bar">CAN bus writes affect vehicle behavior. Remove device immediately if unexpected behavior occurs. Not affiliated with any vehicle manufacturer.</div>

<div class="modal-backdrop" id="confirm-modal" onclick="dashConfirmBackdrop(event)">
  <div class="modal-card" role="dialog" aria-modal="true" aria-labelledby="confirm-title">
    <div class="modal-title" id="confirm-title">Confirm</div>
    <div class="modal-msg" id="confirm-msg"></div>
    <div class="modal-actions">
      <button class="sniff-btn" id="confirm-cancel" onclick="dashConfirmResolve(false)">Cancel</button>
      <button class="sniff-btn modal-btn-primary" id="confirm-ok" onclick="dashConfirmResolve(true)">Continue</button>
    </div>
  </div>
</div>

<div class="modal-backdrop" id="support-modal" onclick="supportBackdrop(event)">
  <div class="modal-card" role="dialog" aria-modal="true" aria-labelledby="support-title" style="width:min(100%,560px)">
    <div class="modal-title" id="support-title">Support</div>
    <div class="modal-msg" style="margin-top:10px">
      <textarea id="support-body" readonly style="width:100%;min-height:260px;resize:vertical;border:1px solid var(--bd2);border-radius:8px;background:var(--bg);color:var(--tx);padding:10px;font:inherit;line-height:1.5"></textarea>
    </div>
    <div class="modal-actions" style="justify-content:space-between;align-items:center">
      <span id="support-status" style="font-size:11px;color:var(--tx3)"></span>
      <div style="display:flex;gap:8px;flex-wrap:wrap;justify-content:flex-end">
        <button class="sniff-btn" onclick="copySupport()">Copy</button>
        <button class="sniff-btn modal-btn-primary" onclick="openSupportIssue()">Open GitHub Issue</button>
        <button class="sniff-btn" onclick="closeSupport()">Close</button>
      </div>
    </div>
  </div>
</div>


<div class="foot" id="dash-foot"ev-open-can-tools &bull; loading...</div>
<div class="foot" style="margin-top:4px">
  <a href="https://github.com/ev-open-can-tools/ev-open-can-tools" target="_blank" rel="noopener" style="color:var(--acc);text-decoration:none">GitHub</a>
  &bull;
  <a href="https://discord.gg/ZTQKAUTd2F" target="_blank" rel="noopener" style="color:var(--acc);text-decoration:none">Discord</a>
</div>
<div class="foot" style="margin-top:8px;font-size:10px">
  <div style="margin-bottom:4px">Gift with Monero</div>
  <div style="word-break:break-all;color:var(--tx2)">46CJEjnN74N83AZHHYKX3mD9kkV6UJYVjN58PTWvQ6VU8Vvn3tmyExkaC2kq9asD6SZY9weaZqx5o9nf1MxkKbmTKWLUeRD</div>
</div>

<script>
const HW=['Legacy','HW3','HW4'];
const SP3=['Chill','Normal','Hurry'];
const SP4=['Chill','Normal','Hurry','Max','Sloth'];
const $=id=>document.getElementById(id);
let dashLang=localStorage.getItem('dashLang')||((navigator.language||'').toLowerCase().startsWith('zh')?'zh':'en');
const I18N_ZH={
'Light':'浅色','Dark':'深色','Waiting for CAN frames':'等待 CAN 帧','Dashboard disconnected':'仪表盘已断开','Dashboard reconnecting':'仪表盘重连中',
'CAN Bus':'CAN 总线','Injection':'注入','Frame rate':'CAN 帧率','CAN Frame Rate':'CAN 帧率','RX Frames':'接收帧','TX Frames':'发送帧','Errors':'错误','AD Status':'AP 状态','Profile':'配置档','Offset':'偏移','Uptime':'运行时间',
'Offline':'离线','Online':'在线','Active':'运行中','Inactive':'未激活','BLOCKED':'已阻止','Waiting AP':'等待 AP','No frames':'无帧','Sniffer paused':'嗅探暂停',
'Plugins':'插件','Plugin Editor':'插件编辑器','Documentation & examples →':'文档与示例 →','Install Plugin':'安装插件','Maximum plugins: --':'插件上限：--','Plugin JSON URL (https://...)':'插件 JSON 地址 (https://...)','Install':'安装','Upload .json':'上传 .json','Paste JSON (offline)':'粘贴 JSON (离线)','Install from JSON':'从 JSON 安装','No plugins installed':'未安装插件','Plugin name':'插件名称','Quick Rule':'快速规则','Rule Test':'规则测试',
'Configuration':'配置','Device settings':'设备设置','Hardware':'硬件','Speed Profile':'速度配置档','Auto':'自动','CAN Injection':'CAN 注入','Stop Injection':'停止注入','Resume Injection':'恢复注入','Force Activate':'强制激活 FSD','Force FSD Activate':'强制激活 FSD','Force AD selected':'按 FSD 已请求处理','Treat FSD as requested':'按 FSD 已请求处理','Only applies while CAN Injection is active':'仅在 CAN 注入开启时生效','Applies while CAN Injection is active; plugin injection still follows AP Injection Gate':'仅在 CAN 注入开启时生效；插件注入仍遵循 AP 后注入','Applies while CAN Injection is active; plugins still follow AP After-Start Gate':'仅在 CAN 注入开启时生效；插件注入仍遵循 AP 后注入','HW3 Offset Slew':'HW3 偏移平滑','Plugin Replay':'插件重复发送次数','Plugin Repeat Count':'插件重复发送次数','Save':'保存','AP Injection Gate':'AP 后注入','AP After-Start Gate':'AP 后注入','Hold plugin injection until AP or NoA is active':'在 AP 或 NoA 激活前暂停插件注入',
'WiFi Hotspot':'WiFi 热点','Change the WiFi hotspot name and password':'修改 WiFi 热点名称和密码','SSID':'SSID','Password':'密码','Hidden':'隐藏','WiFi Internet':'WiFi 互联网','Not configured':'未配置','Save up to 4 networks (e.g. home + phone hotspot).':'最多保存 4 个网络（如家庭 WiFi + 手机热点）。','Add network':'添加网络','WiFi SSID':'WiFi SSID','Scan':'扫描','Save & Connect':'保存并连接','Use static IP':'使用静态 IP',
'STA-AP Gateway':'STA-AP 网关','Gateway status unavailable':'网关状态不可用','Gateway':'网关','Enable STA-AP NAT routing for hotspot clients when WiFi Internet is connected.':'WiFi 互联网连接后，为热点客户端启用 STA-AP NAT 路由。','Blacklist':'黑名单','Whitelist':'白名单','Strict mode':'严格模式','Save DNS':'保存 DNS','Blocked':'阻断记录','DNS Filter List':'DNS 过滤清单','Add to Whitelist':'加入白名单','Blacklisted':'黑名单','Already whitelisted':'已在白名单','Clear':'清空','No blocked domains recorded':'没有阻断记录','Cleared':'已清空','Gateway not available':'网关不可用','domain is blacklisted':'域名在黑名单中，禁止加入白名单','cannot add domain':'无法加入域名',
'CAN Pins':'CAN 引脚','default':'默认','TX GPIO':'TX GPIO','RX GPIO':'RX GPIO','Reboot required after saving custom pins.':'保存自定义引脚后需要重启。','Dashboard Log':'调试日志','Debug Log':'调试日志','Settings Backup':'设置备份','Export and import device settings':'导出和导入设备设置','Download':'下载','Import':'导入','Support':'支持','Open':'打开',
'Firmware Update':'固件更新','Beta Channel':'Beta 通道','Include pre-release / beta firmware versions':'包含预发布 / beta 固件版本','Auto-Update on Boot':'启动后自动更新','Check and install updates automatically ~15 s after WiFi connects':'WiFi 连接约 15 秒后自动检查并安装更新','Check for Updates':'检查更新','Manual firmware upload':'手动上传固件','Tap to select firmware .bin':'点击选择固件 .bin','Or drag and drop a file here':'或将文件拖放到这里','Uploading...':'上传中...','Flash Firmware':'刷写固件','Reset OTA Credentials':'重置 OTA 凭据',
'System Health':'系统状态','System Status':'系统状态','Hardware and runtime health reported by the ESP32 firmware.':'ESP32 固件上报的硬件与运行状态。','CAN调试':'CAN调试','Enable CAN debug tools':'启用 CAN 调试工具','Shows 2.5.2 debug panels and starts their WebUI polling only while enabled':'显示调试面板，并且只在开启时启动相关 WebUI 轮询','Chip':'芯片','CPU':'CPU','CPU Load':'CPU 负载','Core 0':'核心 0','Core 1':'核心 1','Board Specs':'板载规格','Temperature':'温度','Reset':'重启原因','Heap RAM':'堆内存','Largest Block':'最大连续内存块','Min Free Heap':'历史最低空闲内存','PSRAM':'PSRAM','Tasks':'任务','Flash':'Flash','SPIFFS':'SPIFFS','WiFi RSSI':'WiFi 信号','WiFi Mode':'WiFi 模式','AP Clients':'AP 客户端','Bluetooth LE':'蓝牙 LE','Wireless':'无线','MAC / Firmware':'MAC / 固件','System status unavailable':'系统状态不可用','Monitoring off':'监测关闭','Enable live hardware status sampling':'启用实时硬件状态采样','On':'开启','Off':'关闭','off':'关闭','not enabled':'未启用','unavailable':'不可用','offline':'离线','not present':'不存在','STA online':'STA 在线','STA offline':'STA 离线','supported':'支持','not supported':'不支持','firmware disabled':'固件未启用','warming up':'采样中',
'CAN':'CAN','CAN Sniffer':'CAN 嗅探器','Pause':'暂停','Resume':'继续','Wire IDs':'线束 ID','CAN Recorder':'CAN 记录器','Start Recording':'开始记录','Stop Recording':'停止记录','Ready':'就绪','Saved':'已保存','Recording...':'记录中...','CAN Controller':'CAN 控制器','Last Write Check':'最后写入检查','Reset Stats':'重置统计',
'Cancel':'取消','Continue':'继续','Confirm':'确认','Copy':'复制','Open GitHub Issue':'打开 GitHub Issue','Close':'关闭','Show':'显示','Hide':'隐藏','Loading...':'加载中...','Saving...':'保存中...','Saved! Reboot to apply.':'已保存！重启后生效。','Saved':'已保存','Error':'错误','Save failed':'保存失败','Connection error':'连接错误','Connection to ':'到 ',
'Enabled':'已启用','Disabled':'已禁用','on':'开启','waiting':'等待中','blocked':'已阻断','NAT':'NAT','Connected':'已连接','Connecting to ':'正在连接 ','Delete':'删除','Edit':'编辑','No networks saved.':'未保存网络。','firmware default':'固件默认','saved':'已保存'
};
Object.assign(I18N_ZH,{
  'Configure the device hotspot name, password and visibility. Saved in NVS.':'配置设备热点名称、密码和可见性，保存到 NVS。',
  'Stored in NVS (non-volatile storage). The SSID and password survive firmware updates and reboots. Only a full factory erase via USB clears them.':'保存在 NVS 非易失存储中。SSID 和密码会在固件更新、重启后保留，只有通过 USB 完整擦除出厂设置才会清除。',
  'Hotspot Name':'热点名称',
  'New Password (min 8)':'新密码（至少 8 位）',
  'Hide SSID':'隐藏 SSID',
  "Don't broadcast the hotspot name — clients must enter it manually":'不广播热点名称，客户端需要手动输入。',
  'Changes take effect after reboot. Leave password empty to keep current.':'更改将在重启后生效。密码留空表示保留当前密码。',
  'Up to 4 saved networks. The device tries each in turn until one connects.':'最多保存 4 个网络，设备会依次尝试直到连接成功。',
  'Save up to 4 networks (e.g. home + phone hotspot). Device tries each in turn. Stored in NVS — survives firmware updates.':'最多保存 4 个网络（如家庭 WiFi + 手机热点）。设备会依次尝试连接，并保存在 NVS 中，固件更新后仍会保留。',
  'Static IP (optional)':'静态 IP（可选）',
  'Set a fixed IP configuration instead of using DHCP.':'使用固定 IP 配置，而不是 DHCP 自动获取。',
  'IP (e.g. 192.168.1.100)':'IP（例如 192.168.1.100）',
  'Gateway (e.g. 192.168.1.1)':'网关（例如 192.168.1.1）',
  'Mask (255.255.255.0)':'掩码（255.255.255.0）',
  'DNS (e.g. 8.8.8.8)':'DNS（例如 8.8.8.8）',
  'Routes hotspot clients through the configured WiFi Internet uplink, with DNS filtering.':'通过已配置的 WiFi 互联网连接为热点客户端转发网络，并执行 DNS 过滤。',
  'Enable STA-AP NAT routing for hotspot clients when WiFi Internet is connected':'WiFi 互联网连接后，为热点客户端启用 STA-AP NAT 路由。',
  'Strict DNS mode':'严格 DNS 模式',
  'Blocked domains, one per line':'阻止域名，每行一个',
  'Allowed domains, one per line':'允许域名，每行一个',
  'Test domain':'测试域名',
  'Test DNS':'测试 DNS',
  'DNS test failed':'DNS 测试失败',
  'would be blocked':'会被阻断',
  'would be allowed':'会被放行',
  'matched blacklist':'命中黑名单',
  'not in blacklist':'不在黑名单中',
  'matched whitelist':'命中白名单',
  'not in whitelist':'不在白名单中',
  'gateway disabled':'网关未启用',
  'empty domain':'域名为空',
  'Filtered DNS Entries':'DNS 过滤记录',
  'items':'条',
  'Only non-blacklist domains can be added to the whitelist.':'只有非黑名单域名可以加入白名单。',
  'Blacklist blocked':'黑名单禁止加入白名单',
  'Not allowed':'不可加入',
  'DNS filter list unavailable':'DNS 过滤记录不可用'
  ,'Enter hotspot name':'请输入热点名称'
  ,'Password min 8 chars':'密码至少 8 位'
  ,'Scanning...':'扫描中...'
  ,'Save Changes':'保存更改'
});
Object.assign(I18N_ZH,{
  // Core terminology refinements (Tesla FSD / CAN context)
  'Stop Injection':'停止 CAN 注入','Resume Injection':'恢复 CAN 注入','Stop Injecting':'停止 CAN 注入',
  'Heap RAM':'堆内存','Largest Block':'最大连续内存块','Min Free Heap':'历史最低空闲内存',
  // Header / status
  'Reboot':'重启设备','RX':'接收','TX':'发送','TX Errors':'发送错误','Follow dist':'跟车距离','Speed Offset':'限速偏移','Limit Offset':'限速偏移',
  'AD active — injecting':'AP 已激活 — CAN 注入运行中',
  'AP active — injecting':'AP 已激活 — CAN 注入运行中',
  'FSD requested — injecting':'FSD 已请求 — CAN 注入运行中',
  'CAN active — injecting':'CAN 在线 — 注入运行中',
  'Waiting for AP — injection armed':'等待 AP — 注入待命',
  'CAN active — monitoring':'CAN 在线 — 监听中',
  'Stop injecting? This remains disabled after reboot until you press Resume Injection.':'停止 CAN 注入？该状态在重启后仍保持，直到按下"恢复 CAN 注入"。',
  'Stop injection':'停止 CAN 注入','Stop':'停止',
  'Reboot device?':'重启设备？',
  // System Health card
  'cores':'核',
  // Plugins card
  'Install and manage JSON plugins that modify CAN messages in real time.':'安装并管理可实时修改 CAN 报文的 JSON 插件。',
  'Plugins are JSON rules that modify CAN messages in real time. Install via URL, file upload or paste.':'插件是用于实时修改 CAN 报文的 JSON 规则，支持 URL 安装、文件上传或粘贴 JSON。',
  'Install a plugin from a URL or uploaded JSON file.':'通过 URL 或上传的 JSON 文件安装插件。',
  'Paste a full plugin JSON document directly into the editor below.':'将完整的插件 JSON 直接粘贴到下方编辑器中。',
  'When enabled, plugins inject only after Autopilot is observed active.':'开启后，插件只会在检测到 Autopilot 激活后注入。',
  'Frames received per second':'每秒接收 CAN 帧数',
  'Set how many modified GTW 2047 plugin frames are sent immediately per observed frame.':'设置每观察到一帧 GTW 2047 后立即发出的修改帧数量。',
  'GTW 2047 Replay Count':'GTW 2047 重放次数',
  'Modified GTW_autopilot frames sent per observed 0x7FF frame':'每观察到一帧 0x7FF 后发送的 GTW_autopilot 修改帧数',
  'Author (optional)':'作者（可选）','Version':'版本',
  'Fast builder':'快速构建','Live frame preview':'实时帧预览','Add Shortcut':'添加快捷规则',
  'Build, edit and test plugin rules without writing JSON by hand.':'无需手写 JSON 即可构建、编辑和测试插件规则。',
  'Build or edit a plugin via form — no JSON writing needed. Load an installed plugin into the editor, change rules, then reinstall it. You can also send a temporary test frame for one rule before installing.':'通过表单构建或编辑插件，无需手写 JSON。可将已安装插件加载进编辑器修改规则后重新安装；安装前还可针对某条规则发送临时测试帧。',
  'Create one plugin rule quickly from a shorthand CAN line.':'从一行简写的 CAN 语句快速创建一条插件规则。',
  'Preview one rule on a live CAN frame, then inject the modified frame.':'对一条规则在实时 CAN 帧上预览，然后注入修改后的帧。',
  'Choose one rule from the editor. The dashboard waits for the next matching CAN frame, applies that rule to the live frame, then injects it the number of times you set below, spaced by the delay in milliseconds.':'从编辑器中选择一条规则。仪表盘会等待下一帧匹配的 CAN 报文，对实时帧应用该规则，并按下方设置的次数和毫秒间隔注入。',
  'Amount of times':'注入次数','Interval (ms)':'间隔（毫秒）',
  'Add a rule to preview a test frame.':'添加规则后即可预览测试帧。',
  'Select a rule to test.':'请选择要测试的规则。','No rules':'无规则',
  'Add Rule':'添加规则','+ Add Rule':'+ 添加规则','Remove Rule':'删除规则',
  'Idle':'空闲','Start Test':'开始测试','Stop Test':'停止测试','Done':'完成',
  'Download JSON':'下载 JSON','JSON Preview':'JSON 预览','Reset':'重置','Author':'作者',
  // Configuration card
  'Device settings for hardware mode, WiFi, CAN pins, logging and backup.':'设备的硬件模式、WiFi、CAN 引脚、日志与备份设置。',
  'Select the autopilot hardware generation and matching speed profile set.':'选择 Autopilot 硬件代际和对应的速度配置档。',
  'Autopilot generation':'Autopilot 代际',
  'Available profiles depend on the selected hardware.':'可用配置档取决于所选硬件。',
  'Auto follows the vehicle follow distance.':'自动模式跟随车辆跟车距离。',
  'Manual SP3 profile is locked.':'已锁定手动 SP3 配置档。',
  'Manual SP4 profile is locked.':'已锁定手动 SP4 配置档。',
  'Profiles are only available on HW3 and HW4.':'仅 HW3 与 HW4 支持配置档。',
  // Force Activate
  'When enabled, CAN Injection ignores the vehicle UI trigger bit and treats AD as selected. Plugin injection still follows AP Injection Gate.':'开启后，忽略车辆 UI 的 FSD 触发位，CAN 注入按 FSD 已请求处理；插件注入仍遵循 AP 后注入门控。',
  'When enabled, CAN Injection ignores the vehicle UI FSD trigger bit and treats FSD as requested. Plugin injection still follows AP Injection Gate.':'开启后，忽略车辆 UI 的 FSD 触发位，CAN 注入按 FSD 已请求处理；插件注入仍遵循 AP 后注入门控。',
  'Applies while CAN Injection is active; plugin injection still follows AP Injection Gate':'仅在 CAN 注入开启时生效；插件注入仍遵循 AP 后注入门控',
  'Applies while CAN Injection is active; plugins still follow AP After-Start Gate':'仅在 CAN 注入开启时生效；插件注入仍遵循 AP 后注入门控',
  // HW3 Custom Speed
  'HW3 Custom Speed Limit':'HW3 自定义限速',
  'Legacy Custom Speed Limit':'Legacy 自定义限速',
  'Raise UI_mppSpeedLimit on CAN 760 byte 6 to a target km/h based on what the gateway is currently sending. Same bucket layout as HW3. Only writes when target is higher than current — never lowers.':'根据网关当前发送的 UI_mppSpeedLimit (CAN 760 byte 6) 按桶查表得到目标 km/h，仅在目标值高于当前值时写回，从不降低。桶布局与 HW3 一致。',
  'Master enable':'总开关',
  'Allow this module to write to UI_mppSpeedLimit':'允许此模块写入 UI_mppSpeedLimit',
  'Bus raw':'总线原始值',
  'Sent raw':'写入原始值',
  'Override AP fused speed limit by writing a synthetic offset into 1021 mux 2. Custom uses the per-bucket table; High-speed uses target km/h values above 80 km/h.':'通过向 1021 mux 2 写入合成偏移来覆盖 AP 融合限速。Custom 使用分段表；High-speed 处理 80 km/h 以上的目标速度。',
  'Custom table':'自定义分段表',
  '30/40/50/60/70 km/h buckets':'30/40/50/60/70 km/h 分段',
  'High-speed boost (≥80 km/h)':'高速档（≥80 km/h）',
  '80/100/120 km/h target speeds':'80/100/120 km/h 目标速度',
  'Wire encoding':'报文编码',
  'PCT4=current, KPH5=legacy fleets':'PCT4=当前编码，KPH5=旧版车队',
  'Fused':'融合限速','Stock off':'原车限速偏移','Stock limit offset':'原车限速偏移','Tgt raw':'写入 raw','Write raw':'写入 raw',
  // HW3 slew
  'Limits downward HW3 mux 2 offset changes sent by enabled dashboard plugins.':'限制 HW3 mux 2 限速偏移下调速度，避免限速突降时一次性写入过低 offset。',
  'When enabled, plugin injection waits for AP, Park or Summon. Built-in Force FSD Activate is not gated by this switch.':'开启后，插件注入需等待检测到 AP、泊车或召唤状态允许；内置强制激活 FSD 不受此开关限制。',
  'Ramp-down limiter':'下行限速器',
  'Opt-in only; increases still pass immediately':'仅手动开启，向上调整仍立即生效',
  'Slew Rate':'限速偏移下降速率','Offset drop rate':'限速偏移下降速率','Target':'目标','Last':'上次','Capped':'触发限制',
  // AP Injection Gate
  'Start after AP':'AP 激活后启动',
  // WiFi
  'No networks saved.':'未保存网络。','No networks found':'未找到网络',
  'Edit':'编辑','Delete':'删除','Delete WiFi':'删除 WiFi',
  'Leave empty to keep current':'留空表示保留当前密码',
  'Password required':'请输入密码','Enter SSID':'请输入 SSID','Scan failed':'扫描失败',
  // STA-AP Gateway
  'Routes hotspot clients through the configured WiFi Internet uplink, with DNS filtering.':'通过已配置的 WiFi 互联网上行为热点客户端转发，并提供 DNS 过滤。',
  'Blacklist Mode':'黑名单模式','Whitelist Mode':'白名单模式',
  'Refresh Blocked IPs':'刷新已阻断 IP','Clear Blocked IPs':'清空已阻断 IP',
  'Filter List':'过滤清单','Clear':'清空',
  'Strict Mode IPs':'严格模式 IP','Refresh':'刷新',
  'Current: Blacklist mode - saving automatically':'当前：黑名单模式 - 自动保存中',
  'Current: Whitelist mode - saving automatically':'当前：白名单模式 - 自动保存中',
  'Current: Blacklist mode - click mode to save immediately':'当前：黑名单模式 - 点击模式立即保存',
  'Current: Whitelist mode - click mode to save immediately':'当前：白名单模式 - 点击模式立即保存',
  'Current: Blacklist mode - saved':'当前：黑名单模式 - 已保存',
  'Current: Whitelist mode - saved':'当前：白名单模式 - 已保存',
  'Already in blacklist':'已在黑名单',
  'Gateway not available':'网关不可用',
  'No blocked IPs recorded':'尚无阻断 IP 记录',
  'Blocked IP list unavailable':'阻断 IP 列表不可用',
  // CAN Pins
  'Save CAN pins':'保存 CAN 引脚',
  'Reboot required after change':'修改后需要重启',
  'Enter both TX and RX':'请同时填写 TX 和 RX',
  'Saved. Rebooting...':'已保存，重启中...',
  // Dashboard log
  'Recent dashboard output':'最近调试输出',
  'Recent debug output':'最近调试输出',
  'Shows recent dashboard and firmware log lines. This is the dashboard logging output, not the CAN sniffer.':'显示最近 WebUI 与固件日志；这不是 CAN 嗅探器。',
  'Shows recent WebUI and firmware log lines. This is debug logging output, not the CAN sniffer.':'显示最近 WebUI 与固件日志；这不是 CAN 嗅探器。',
  'Turns dashboard log output on or off.':'开启或关闭 WebUI 与固件调试日志输出。',
  'Turns WebUI debug log output on or off.':'开启或关闭 WebUI 与固件调试日志输出。',
  'Dashboard Logging':'调试日志开关',
  'Debug logging':'调试日志开关',
  'Toggle dashboard log output':'开启或关闭 WebUI 与固件调试日志输出',
  'Toggle WebUI and firmware debug output':'开启或关闭 WebUI 与固件调试日志输出',
  'Waiting...':'等待中...','Loading...':'加载中...','Saving...':'保存中...','Checking...':'检查中...',
  'Downloading...':'下载中...','Uploading...':'上传中...','Installing...':'安装中...',
  'Preparing...':'准备中...','Downloaded':'已下载','Installed':'已安装',
  // Settings backup
  'Export or restore saved device settings as JSON.':'导出或还原已保存的设备设置（JSON 格式）。',
  'Upload & Restore':'上传并还原',
  'Restore settings':'还原设置','Restore':'还原',
  'Export failed':'导出失败','Invalid JSON':'JSON 格式错误',
  'Restored. Rebooting...':'已还原，重启中...','Import failed':'导入失败','Upload failed':'上传失败',
  // Support
  'Copy a status summary before opening a GitHub issue':'在提交 GitHub 问题前复制一份状态摘要',
  'Collect a support summary and open a GitHub issue with the details prefilled.':'收集支持信息摘要，并以预填详情打开 GitHub 问题。',
  'Copy this text, then open the GitHub issue form.':'复制下方文本后再打开 GitHub 问题表单。',
  'Copied to clipboard':'已复制到剪贴板','Copy failed':'复制失败',
  'Copied support details. Paste them into the support question.':'已复制支持信息，请粘贴到问题描述中。',
  // Firmware update
  'Version info':'版本信息',
  'Check for updates, enable beta builds and upload firmware manually.':'检查更新、启用 Beta 构建或手动上传固件。',
  'Shows pre-release firmware versions when available.':'若有预发布版本则一并显示。',
  'Checks for firmware updates automatically shortly after WiFi connects.':'WiFi 连接后自动检查固件更新。',
  'No update URL':'未提供更新地址',
  'Install firmware update? The device will reboot.':'安装固件更新？设备将会重启。',
  'Install update':'安装更新','Install':'安装',
  'Downloading & installing...':'下载并安装中...',
  'Update installed! Rebooting...':'更新已安装，重启中...',
  'Update failed':'更新失败',
  'Manual firmware upload (.bin)':'手动上传固件 (.bin)',
  'Upload a local firmware .bin file directly to the device.':'将本地固件 .bin 文件直接上传到设备。',
  'Done! Device is rebooting...':'完成！设备正在重启...',
  'OTA Username:':'OTA 用户名：','OTA Password:':'OTA 密码：',
  'Flashing...':'刷写中...','OTA Credentials Reset':'OTA 凭据已重置',
  'Up to date':'已是最新','Update available':'发现可用更新',
  // CAN tools card
  'Sniffer, recorder and bus status':'嗅探、记录与总线状态',
  'Live CAN tools for sniffing, recording, controller status and checking the last injected write.':'实时 CAN 工具：嗅探、记录、控制器状态以及最后写入校验。',
  'Shows the latest 30 CAN frames live. You can filter by ID or name, switch between wire IDs and DBC IDs, and pause the view.':'实时显示最近 30 帧 CAN 报文。可按 ID 或名称过滤，可在线束 ID 和 DBC ID 之间切换并暂停。',
  'Filter by ID or name':'按 ID 或名称过滤',
  'Filter by wire/DBC ID or name':'按 线束/DBC ID 或名称过滤',
  'Records live CAN traffic up to the frame limit and lets you download it as a CSV file.':'实时记录 CAN 报文直到达到上限，可导出为 CSV 文件。',
  'Download CSV':'下载 CSV','Mux':'多路','OK':'正常',
  'Bus-Off':'总线关闭','TX Passive':'TX 被动','RX Passive':'RX 被动',
  'TX Warn':'TX 警告','RX Warn':'RX 警告','RX Overflow':'RX 溢出',
  'Shows CAN controller health, error flags and the RX, TX and error counters per mux.':'显示 CAN 控制器状态、错误标志以及每个 mux 的 RX/TX/错误计数。',
  'Compares the last injected frame with the latest bus frame that has the same CAN ID and mux. Helpful to spot overwrites, but not proof that a module accepted the change.':'比较最近一次注入帧与同一 CAN ID/mux 的最新总线帧。有助于发现覆盖，但不能证明模块已接受变更。',
  'No injected frame yet':'尚未注入帧','Sent':'已发送','Bus':'总线',
  'Waiting for next matching bus frame':'等待下一帧匹配的总线报文',
  'Matching frame seen on bus':'已在总线上看到匹配帧',
  'Latest bus frame differs from injected frame':'最新总线帧与注入帧不一致',
  'Driver transmit failed':'驱动发送失败',
  'No matching RX frame seen yet':'尚未看到匹配的 RX 帧',
  'Reset Stats':'重置统计',
  // CAN debug card
  'Enable the stable 2.5.2 debug tools: plugins, plugin editor, firmware update, dashboard log and live CAN tools.':'启用调试面板：插件、插件编辑器、固件更新、调试日志和实时 CAN 工具。',
  'Enable debug panels: plugins, plugin editor, firmware update, debug log and live CAN tools.':'启用调试面板：插件、插件编辑器、固件更新、调试日志和实时 CAN 工具。',
  // Confirm modal / common
  'Confirm':'确认','Continue':'继续','Cancel':'取消',
  // Warnings
  'CAN bus writes affect vehicle behavior. Remove device immediately if unexpected behavior occurs. Not affiliated with any vehicle manufacturer.':'CAN 总线写入会影响车辆行为。一旦出现异常请立即拔除设备。与任何车厂无关联。',
  // Plugin entries / dialogs
  'Remove this plugin?':'确认删除该插件？','Remove plugin':'删除插件','Remove':'删除',
  'Load installed plugin into the editor? Current editor contents will be replaced.':'将已安装插件加载到编辑器？当前编辑器内容将被替换。',
  'Load plugin':'加载插件','Load':'加载','Discard':'丢弃',
  'Discard current editor contents?':'丢弃当前编辑器内容？','Discard changes':'丢弃更改',
  'Overwrite plugin':'覆盖插件','Overwrite':'覆盖',
  'Plugin name required':'请输入插件名称','Name too long (max 31)':'名称过长（最多 31 字符）',
  'Add at least one rule':'至少添加一条规则',
  'Max 16 rules per plugin':'每个插件最多 16 条规则',
  'Shortcut added':'已添加快捷规则',
  'Shortcut line required':'请输入快捷规则',
  'Use format like 0x7FF mux=2 byte[5] = 0x4C':'格式示例：0x7FF mux=2 byte[5] = 0x4C',
  'CAN ID must be 1-0x7FF':'CAN ID 必须在 1-0x7FF 范围',
  'mux must be -1..255':'mux 必须在 -1..255 范围',
  'byte must be 0-7':'byte 必须在 0-7 范围',
  'value must be 0-255':'value 必须在 0-255 范围',
  'mask must be 0-255':'mask 必须在 0-255 范围',
  'Test failed':'测试失败','Starting...':'启动中...',
  'Add a rule first':'请先添加规则','Select a valid rule':'请选择有效的规则',
  'Count must be 1-200':'次数必须为 1-200','Interval must be 10-5000 ms':'间隔必须为 10-5000 毫秒',
  'Paste JSON first':'请先粘贴 JSON',
  'Enter URL':'请输入 URL','Connection error':'连接错误',
  // Plugin priority
  'Injection priority':'注入优先级',
  'No enabled plugins are injecting frames.':'当前没有插件在注入帧。',
  'Priority overlap':'优先级重叠',
  'Lower priority bits are ignored':'低优先级位将被忽略',
  // Sniffer
  'Showing on-wire 11-bit CAN IDs':'显示线束上的 11 位 CAN ID',
  // Bottom bits
  'Hide':'隐藏','Show':'显示',
  'Recording...':'记录中...',
  // Plugin editor preview
  'No ops — add one below':'暂无操作 — 请在下方添加'
});
const I18N_EN={};Object.keys(I18N_ZH).forEach(k=>I18N_EN[I18N_ZH[k]]=k);
const I18N_RX=[
  [/^Enabled \u2022 NAT on \u2022 blocked (\d+)$/,'已启用 \u2022 NAT 开启 \u2022 已阻断 $1'],
  [/^Enabled \u2022 NAT waiting \u2022 blocked (\d+)$/,'已启用 \u2022 NAT 等待中 \u2022 已阻断 $1'],
  [/^Disabled \u2022 NAT waiting \u2022 blocked (\d+)$/,'已禁用 \u2022 NAT 等待中 \u2022 已阻断 $1'],
  [/^Connected: (.+) \u2022 ([0-9a-fA-F:.]+) \u2022 switch to that WiFi and open this IP$/,'已连接：$1 \u2022 $2 \u2022 请切换到该 WiFi 并打开此 IP'],
  [/^Connected: (.+) \u2022 ([0-9a-fA-F:.]+)$/,'已连接：$1 \u2022 $2'],
  [/^Add network \((\d+)\/(\d+)\)$/,'添加网络 ($1/$2)'],
  [/^Connected: (.+)$/,'已连接：$1'],[/^Connecting to (.+)\.\.\.$/,'正在连接 $1...'],
  [/^(\d+) saved \u2022 trying to connect\.\.\.$/,'已保存 $1 个 \u2022 正在尝试连接...'],
  [/^(\d+) client(s?)$/,'$1 个客户端'],[/^(\d+) frames$/,'$1 帧'],[/^(\d+) \/ (\d+) frames$/,'$1 / $2 帧'],
  [/^(\d+) frames saved$/,'已保存 $1 帧'],
  [/^Up to date \(v(.+)\)$/,'已是最新 (v$1)'],[/^Update available!$/,'发现可用更新！'],
  [/^Enabled • NAT on • blocked (\d+) • strict \(allow (\d+) \/ block (\d+)\)$/,'已启用 • NAT 开启 • 已阻断 $1 • 严格 (允许 $2 / 阻断 $3)'],
  [/^Enabled • NAT waiting • blocked (\d+) • strict \(allow (\d+) \/ block (\d+)\)$/,'已启用 • NAT 等待中 • 已阻断 $1 • 严格 (允许 $2 / 阻断 $3)'],
  [/^Disabled • NAT waiting • blocked (\d+) • strict \(allow (\d+) \/ block (\d+)\)$/,'已禁用 • NAT 等待中 • 已阻断 $1 • 严格 (允许 $2 / 阻断 $3)'],
  [/^(.+) • (\d+) cores • (\d+) MHz now$/,'$1 • $2 核 • 当前 $3 MHz'],
  [/^(\d+) cores • now (\d+) MHz • max (\d+) MHz$/,'$1 核 • 当前 $2 MHz • 最大 $3 MHz'],
  [/^CPU0 (\d+)% • CPU1 (\d+)%$/,'CPU0 $1% • CPU1 $2%'],
  [/^(\d+) tasks$/,'$1 个任务'],
  [/^(\d+) installed$/,'已安装 $1 个'],
  [/^(\d+) \/ (\d+) installed$/,'已安装 $1 / $2 个'],
  [/^(\d+) rule$/,'$1 条规则'],[/^(\d+) rules$/,'$1 条规则'],
  [/^Maximum (\d+) plugins reached\. Remove one before installing another\.$/,'已达到 $1 个插件上限，请先移除一个再安装。'],
  [/^Maximum (\d+) plugins total\. Remove one before installing another\.$/,'插件上限 $1 个，请先移除一个再安装。'],
  [/^Max (\d+) networks$/,'最多 $1 个网络'],
  [/^Delete network "(.+)"\?$/,'确认删除网络 "$1"？'],
  [/^Save CAN pins TX=(\d+) RX=(\d+) and reboot\? Wrong pins disable CAN\.$/,'保存 CAN 引脚 TX=$1 RX=$2 并重启？错误引脚会导致 CAN 无法工作。'],
  [/^custom TX=(\d+) RX=(\d+)$/,'自定义 TX=$1 RX=$2'],
  [/^firmware default TX=(\d+) RX=(\d+)$/,'固件默认 TX=$1 RX=$2'],
  [/^Restore settings from (.+) and reboot\?$/,'从 $1 还原设置并重启？'],
  [/^Loaded "(.+)" into editor$/,'已将 "$1" 加载到编辑器'],
  [/^A plugin named "(.+)" already exists\. Overwrite\?$/,'已存在名为 "$1" 的插件，是否覆盖？'],
  [/^Use 1-(\d+)$/,'请输入 1-$1'],
  [/^Done (\d+)\/(\d+)$/,'已完成 $1/$2'],
  [/^Stopped (\d+)\/(\d+)$/,'已停止 $1/$2'],
  [/^Running (\d+)\/(\d+) · every (\d+) ms$/,'运行中 $1/$2 · 间隔 $3 毫秒'],
  [/^Waiting for CAN 0x([0-9A-Fa-f]+)$/,'等待 CAN 0x$1'],
  [/^Whitelist (\d+)\/(\d+) • Blacklist (\d+)\/(\d+)$/,'白名单 $1/$2 • 黑名单 $3/$4'],
  [/^allowed (\d+) • blocked (\d+)$/,'允许 $1 • 阻断 $2'],
  [/^Connection to (.+) lost\. Reload after reconnecting\.$/,'与 $1 的连接已断开，重新连接后请刷新。'],
  [/^Connection to (.+) lost\. Switch to your normal WiFi and open http:\/\/(.+)$/,'与 $1 的连接已断开，请切换到常用 WiFi 后打开 http://$2'],
  [/^(\d+)%\/s \(about ([\d.]+) km\/h\/s at 60 km\/h\)$/,'$1%/秒（60 km/h 时约 $2 km/h/秒）'],
  [/^(\d+)%\/s$/,'$1%/秒'],
  [/^Showing DBC JSON IDs with (.+) prefix$/,'显示带 $1 前缀的 DBC JSON ID']
];
function trText(value){
  let s=String(value);
  if(dashLang!=='zh')return I18N_EN[s]||s;
  if(I18N_ZH[s])return I18N_ZH[s];
  for(const r of I18N_RX){if(r[0].test(s))return s.replace(r[0],r[1]);}
  return s;
}
const setText=(id,value)=>{const el=$(id);if(el)el.textContent=trText(value);};
const setClass=(id,value)=>{const el=$(id);if(el)el.className=value;};
function profileNamesForHw(hw){return hw===2?SP4:SP3;}
function profileDisplayName(hw,sp,auto){
  const name=(profileNamesForHw(hw)||[])[clampProfileForHw(hw,sp)]||'—';
  return auto?'Auto ('+name+')':name;
}
function gtwAutopilotName(v){
  return ['NONE','HIGHWAY','ENHANCED','SELF_DRIVING','BASIC'][v]||'UNKNOWN';
}
function gtwAutopilotShort(v,ad){
  v=Number(v);
  if(v===3)return 'AP-FSD';
  if(v===2)return 'AP-EAP';
  if(v===4)return 'AP-BASIC';
  if(v===1)return 'AP-HWY';
  if(v===0)return 'AP-NONE';
  return ad?'AD':'AP-?';
}
function gtwAutopilotBadge(v){
  if(v<0)return 'GTW —';
  if(v===3)return 'GTW SELF';
  return 'GTW '+gtwAutopilotName(v);
}
function injectionStatusLabel(injecting,armed,apGate,d){
  if(injecting){
    const tag=gtwAutopilotShort(d.gtwap,d.apActive);
    return (dashLang==='zh'?'运行中':'Active')+' '+tag;
  }
  if(armed&&apGate)return dashLang==='zh'?'等待 AP':'Waiting AP';
  return dashLang==='zh'?'已阻止':'BLOCKED';
}
function updateGtwBadge(v){
  const el=$('gtw-badge');if(!el)return;
  v=Number(v);
  const known=!isNaN(v)&&v>=0;
  el.textContent=gtwAutopilotBadge(known?v:-1);
  el.className='gtw-badge '+(known?'known':'');
  el.title=known?('GTW_autopilot: '+gtwAutopilotName(v)+' ('+v+')'):'GTW_autopilot: not seen yet';
}
let state={hw:1,can:true,force:false,apGate:false,sp:0,spAuto:true,plgr:1,plgrmax:20,hw3OffsetSlew:false,hw3SlewRate:5};
let sniffPaused=false,sniffFrames=[];
let sniffShowDbcIds=localStorage.getItem('sniffIdMode')==='dbc';
let otaFile=null;
let otaUser=localStorage.getItem('otaU')||'',otaPass=localStorage.getItem('otaP')||'';
let logSince=0;
let installedPlugins=[];
let pluginMax=0;
const peMaxOps=16;
let peLoadedPluginName='';
let peTestPollTimer=null;
let pluginDetailOpen={};
let dashConfirmState=null;
let supportIssueUrl='https://github.com/ev-open-can-tools/ev-open-can-tools/issues/new?template=issue.yml';
let supportBodyText='';
let dashboardPollTimers=[];
let dashboardPollFailures=0;
let dashboardStatusOk=false;
let dashboardInitialLoaded=false;
let dashboardPollStopped=false;
let systemStatusTimer=null;
let systemStatusEnabled=false;
let dashboardStaIp='';
let canDebugEnabled=localStorage.getItem('canDebug')==='1';
let canDebugPollTimers=[];
const pollLocks={};

function stopDashboardPolling(){
  if(dashboardPollStopped)return;
  dashboardPollStopped=true;
  dashboardPollTimers.forEach(clearInterval);
  dashboardPollTimers=[];
  if(systemStatusTimer){clearInterval(systemStatusTimer);systemStatusTimer=null;}
  stopCanDebugPolling();
  $('dot').className='sdot dot-off';
  $('hdr-desc').textContent='Dashboard disconnected';
  let msg='Connection to '+location.hostname+' lost. Reload after reconnecting.';
  if(dashboardStaIp&&dashboardStaIp!==location.hostname)msg='Connection to '+location.hostname+' lost. Switch to your normal WiFi and open http://'+dashboardStaIp;
  $('wifi-status').textContent=msg;
  $('wifi-status').style.color='var(--err)';
}

function setCanDebugUi(){
  document.body.classList.toggle('can-debug-on',canDebugEnabled);
  const t=$('can-debug-tgl');if(t)t.checked=canDebugEnabled;
  setText('can-debug-meta',canDebugEnabled?'On':'Off');
}
function positionCanDebugPanels(){
  const anchor=$('can-debug-card');if(!anchor)return;
  let after=anchor;
  Array.from(document.querySelectorAll('body > .can-debug-panel')).forEach(panel=>{
    if(panel!==after.nextSibling)after.parentNode.insertBefore(panel,after.nextSibling);
    after=panel;
  });
}
function startCanDebugPolling(){
  if(canDebugPollTimers.length||dashboardPollStopped)return;
  canDebugPollTimers.push(setInterval(pollLog,5000));
  canDebugPollTimers.push(setInterval(pollSniffer,1000));
  canDebugPollTimers.push(setInterval(pollPlugins,10000));
  pollLog();pollSniffer();pollPlugins();pollRec();loadUpdateInfo();peRender();
}
function stopCanDebugPolling(){
  canDebugPollTimers.forEach(clearInterval);
  canDebugPollTimers=[];
  if(recIsActive){stopRec();}
  peStopTestPoll();
}
function applyCanDebug(){
  setCanDebugUi();
  if(canDebugEnabled)startCanDebugPolling();
  else stopCanDebugPolling();
}
function toggleCanDebug(){
  canDebugEnabled=!!$('can-debug-tgl').checked;
  localStorage.setItem('canDebug',canDebugEnabled?'1':'0');
  applyCanDebug();
}

function noteDashboardPoll(ok){
  if(ok){dashboardPollFailures=0;dashboardStatusOk=true;return;}
  if(dashboardPollStopped)return;
  dashboardStatusOk=false;
  dashboardPollFailures++;
  $('dot').className='sdot dot-off';
  $('hdr-desc').textContent='Dashboard reconnecting';
}

async function fetchPollJson(url,timeoutMs,trackConnection){
  const ctrl=new AbortController();
  const timer=setTimeout(()=>ctrl.abort(),timeoutMs||2500);
  try{
    const r=await fetch(url,{signal:ctrl.signal});
    if(!r.ok)throw new Error('HTTP '+r.status);
    const d=await r.json();
    if(trackConnection)noteDashboardPoll(true);
    return d;
  }catch(e){
    if(trackConnection)noteDashboardPoll(false);
    throw e;
  }finally{
    clearTimeout(timer);
  }
}

async function runPoll(name,fn){
  if(dashboardPollStopped||pollLocks[name])return;
  pollLocks[name]=true;
  try{return await fn();}finally{pollLocks[name]=false;}
}

function waitMs(ms){return new Promise(resolve=>setTimeout(resolve,ms));}

function initCardMinimizers(){
  document.querySelectorAll('.card').forEach((card,i)=>{
    const hdr=card.querySelector('.card-hdr');if(!hdr||hdr.querySelector('.card-min-btn'))return;
    const title=card.querySelector('.card-title');
    const key='cardCollapse:'+i+':'+((title?title.textContent:'card').trim().toLowerCase().replace(/[^a-z0-9]+/g,'-'));
    card.dataset.collapseKey=key;
    const btn=document.createElement('button');
    btn.type='button';
    btn.className='sniff-btn card-min-btn';
    btn.onclick=()=>{
      const collapsed=!card.classList.contains('collapsed');
      card.classList.toggle('collapsed',collapsed);
      localStorage.setItem(key,collapsed?'1':'0');
      btn.textContent=collapsed?'Show':'Hide';
    };
    hdr.appendChild(btn);
    const collapsed=localStorage.getItem(key)==='1';
    card.classList.toggle('collapsed',collapsed);
    btn.textContent=collapsed?'Show':'Hide';
  });
}
function initSubsectionMinimizers(){
  document.querySelectorAll('.subsec').forEach((sec,i)=>{
    const hdr=sec.querySelector('.subsec-head');if(!hdr||hdr.querySelector('.subsec-btn'))return;
    const explicitKey=sec.dataset.subkey||'';
    const title=sec.querySelector('.subsec-title');
    const safe=((title?title.textContent:'section').trim().toLowerCase().replace(/[^a-z0-9]+/g,'-'));
    const key='subCollapse:'+(explicitKey||i+':'+safe);
    sec.dataset.collapseKey=key;
    const btn=document.createElement('button');
    btn.type='button';
    btn.className='sniff-btn subsec-btn';
    btn.onclick=()=>{
      const collapsed=!sec.classList.contains('collapsed');
      sec.classList.toggle('collapsed',collapsed);
      localStorage.setItem(key,collapsed?'1':'0');
      btn.textContent=collapsed?'Show':'Hide';
    };
    hdr.appendChild(btn);
    const collapsed=localStorage.getItem(key)==='1';
    sec.classList.toggle('collapsed',collapsed);
    btn.textContent=collapsed?'Show':'Hide';
  });
}

function syncSniffPauseButton(){
  const b=$('sniff-pause-btn');if(!b)return;
  b.textContent=sniffPaused?'Resume':'Pause';
  b.classList.toggle('paused',sniffPaused);
}

function actionErrorMessage(e,fallback){
  if(!e)return fallback;
  if(e.name==='AbortError'||e.name==='SyntaxError'||e.message==='Failed to fetch'||e.message==='Empty response')return fallback;
  return e.message||fallback;
}

async function fetchJsonWithTimeout(url,options,timeoutMs){
  const ctrl=new AbortController();
  const timer=setTimeout(()=>ctrl.abort(),timeoutMs||2500);
  try{
    const opts=Object.assign({},options||{});
    opts.signal=ctrl.signal;
    const r=await fetch(url,opts);
    const text=await r.text();
    if(!text||!text.trim())throw new Error(r.ok?'Empty response':('HTTP '+r.status));
    const d=JSON.parse(text);
    if(!r.ok)throw new Error(d.error||('HTTP '+r.status));
    return d;
  }finally{
    clearTimeout(timer);
  }
}

function dashConfirmResolve(ok){
  if(!dashConfirmState)return;
  const resolve=dashConfirmState.resolve;
  dashConfirmState=null;
  $('confirm-modal').style.display='none';
  document.body.style.overflow='';
  resolve(!!ok);
}

function dashConfirmBackdrop(ev){
  if(ev.target===$('confirm-modal'))dashConfirmResolve(false);
}

function supportBackdrop(ev){
  if(ev.target===$('support-modal'))closeSupport();
}

function dashConfirm(message,title,okText,cancelText){
  if(dashConfirmState)dashConfirmResolve(false);
  return new Promise(resolve=>{
    dashConfirmState={resolve};
    $('confirm-title').textContent=title||'Confirm';
    $('confirm-msg').textContent=message||'';
    $('confirm-ok').textContent=okText||'Continue';
    $('confirm-cancel').textContent=cancelText||'Cancel';
    $('confirm-modal').style.display='flex';
    document.body.style.overflow='hidden';
    setTimeout(()=>{$('confirm-ok').focus();},0);
  });
}

function supportPluginSummary(){
  return (installedPlugins||[]).filter(p=>p&&p.enabled).map(function(p){
    return '#'+p.priority+' '+p.name+(p.rules?' ('+p.rules+' rules)':'');
  }).join('\n')||'none';
}

function supportSettingsSummary(){
  return [
    'Hardware: '+(HW[state.hw]||'?'),
    'Speed profile: '+profileDisplayName(state.hw,state.sp,state.spAuto),
    'CAN status: '+($('s-can')?$('s-can').textContent:'--'),
    'Injection: '+($('s-inj')?$('s-inj').textContent:'--'),
    'AD: '+($('s-AD')?$('s-AD').textContent:'--'),
    'CAN pins: '+($('can-pins-status')?$('can-pins-status').textContent:'--'),
    'Firmware: '+($('fw-ver')?$('fw-ver').textContent:'--'),
    'Beta channel: '+($('beta-tgl')&&$('beta-tgl').checked?'enabled':'disabled'),
    'Auto-update: '+($('auto-upd-tgl')&&$('auto-upd-tgl').checked?'enabled':'disabled'),
    'Force activate: '+(state.force?'enabled':'disabled'),
    'HW3 offset slew: '+(state.hw3OffsetSlew?'enabled @ '+(state.hw3SlewRate||5)+'%/s':'disabled'),
    'Plugin replay: '+(state.plgr||1)+'x',
    'Dashboard logging: '+($('tgl-eprn')&&$('tgl-eprn').checked?'enabled':'disabled')
  ].join('\n');
}

function buildSupportBody(){
  const enabled=supportPluginSummary();
  const body=[
    'ev-open-can-tools support report',
    '',
    'Device',
    'Hardware: '+(HW[state.hw]||'?'),
    'Speed profile: '+profileDisplayName(state.hw,state.sp,state.spAuto),
    'CAN status: '+($('s-can')?$('s-can').textContent:'--'),
    'Injection: '+($('s-inj')?$('s-inj').textContent:'--'),
    'AD: '+($('s-AD')?$('s-AD').textContent:'--'),
    'CAN pins: '+($('can-pins-status')?$('can-pins-status').textContent:'--'),
    'Firmware: '+($('fw-ver')?$('fw-ver').textContent:'--'),
    '',
    'Settings',
    'Beta channel: '+($('beta-tgl')&&$('beta-tgl').checked?'enabled':'disabled'),
    'Auto-update: '+($('auto-upd-tgl')&&$('auto-upd-tgl').checked?'enabled':'disabled'),
    'Force activate: '+(state.force?'enabled':'disabled'),
    'HW3 offset slew: '+(state.hw3OffsetSlew?'enabled @ '+(state.hw3SlewRate||5)+'%/s':'disabled'),
    'Plugin replay: '+(state.plgr||1)+'x',
    'Dashboard logging: '+($('tgl-eprn')&&$('tgl-eprn').checked?'enabled':'disabled'),
    '',
    'Enabled plugins',
    enabled,
    '',
    'Notes',
    ''
  ].join('\n');
  supportBodyText=body;
  return body;
}

function openSupport(){
  const el=$('support-body');
  if(el)el.value=buildSupportBody();
  const st=$('support-status');
  if(st){st.textContent='Copy this text, then open the GitHub issue form.';st.style.color='var(--tx3)';}
  $('support-modal').style.display='flex';
  document.body.style.overflow='hidden';
  setTimeout(()=>{if(el)el.focus();el&&el.setSelectionRange(0,0);},0);
}

function closeSupport(){
  $('support-modal').style.display='none';
  document.body.style.overflow='';
}

function copySupportText(text,el){
  if(el){
    el.focus();
    el.select();
    el.setSelectionRange(0,text.length);
    if(document.execCommand&&document.execCommand('copy'))return true;
  }
  if(navigator.clipboard&&navigator.clipboard.writeText){
    navigator.clipboard.writeText(text).catch(()=>{});
    return true;
  }
  return false;
}

function copySupport(){
  const el=$('support-body');
  const text=el?el.value:buildSupportBody();
  if(copySupportText(text,el)){
    const st=$('support-status');if(st){st.textContent='Copied to clipboard';st.style.color='var(--ok)';}
    return true;
  }
  const st=$('support-status');if(st){st.textContent='Copy failed';st.style.color='var(--err)';}
  return false;
}

function openSupportIssue(){
  const url='https://github.com/ev-open-can-tools/ev-open-can-tools/issues/new?template=issue.yml';
  const copied=copySupport();
  supportIssueUrl=url;
  window.open(url,'_blank','noopener');
  const st=$('support-status');if(st&&copied){st.textContent='Copied support details. Paste them into the support question.';st.style.color='var(--ok)';}
  closeSupport();
}

document.addEventListener('keydown',e=>{
  if(e.key==='Escape'){
    if(dashConfirmState)dashConfirmResolve(false);
    closeHelpPanels(document);
  }
});
document.addEventListener('click',e=>{
  if(!e.target.closest('.title-help')&&!e.target.closest('.inline-help-panel')){
    closeHelpPanels(document);
  }
});

function toggleTheme(){
  const html=document.documentElement;
  const isDark=html.getAttribute('data-theme')==='dark';
  html.setAttribute('data-theme',isDark?'light':'dark');
  $('theme-btn').innerHTML=isDark?'&#9790; '+trText('Dark'):'&#9788; '+trText('Light');
  localStorage.setItem('theme',isDark?'light':'dark');
}
function i18nSkip(el){
  return !el||['SCRIPT','STYLE','TEXTAREA','INPUT','OPTION'].includes(el.nodeName);
}
function i18nNodeText(node){
  if(!node||!node.nodeValue||!node.nodeValue.trim()||i18nSkip(node.parentElement))return;
  const raw=node.nodeValue;
  const lead=(raw.match(/^\s*/)||[''])[0],tail=(raw.match(/\s*$/)||[''])[0];
  const mid=raw.trim();
  const out=trText(mid);
  if(out!==mid)node.nodeValue=lead+out+tail;
}
function i18nElementAttrs(el){
  if(!el||i18nSkip(el))return;
  ['placeholder','title','aria-label'].forEach(a=>{const v=el.getAttribute&&el.getAttribute(a);if(v){const t=trText(v);if(t!==v)el.setAttribute(a,t);}});
}
function applyDashboardI18n(root){
  root=root||document.body;
  if(!root)return;
  if(root.nodeType===Node.TEXT_NODE){i18nNodeText(root);return;}
  i18nElementAttrs(root);
  const walker=document.createTreeWalker(root,NodeFilter.SHOW_TEXT,{acceptNode:n=>i18nSkip(n.parentElement)?NodeFilter.FILTER_REJECT:NodeFilter.FILTER_ACCEPT});
  let n;while((n=walker.nextNode()))i18nNodeText(n);
  root.querySelectorAll&&root.querySelectorAll('[placeholder],[title],[aria-label]').forEach(i18nElementAttrs);
  updateLanguageButton();
}
function updateLanguageButton(){
  const b=$('lang-btn');if(b)b.textContent=dashLang==='zh'?'English':'中文';
}
function toggleLanguage(){
  dashLang=dashLang==='zh'?'en':'zh';
  localStorage.setItem('dashLang',dashLang);
  applyDashboardI18n(document.body);
  const t=document.documentElement.getAttribute('data-theme')||'dark';
  $('theme-btn').innerHTML=t==='dark'?'&#9788; '+trText('Light'):'&#9790; '+trText('Dark');
}
(function(){
  const t=localStorage.getItem('theme')||'dark';
  document.documentElement.setAttribute('data-theme',t);
  // will be updated after DOM ready
  window.addEventListener('DOMContentLoaded',()=>{
    $('theme-btn').innerHTML=t==='dark'?'&#9788; '+trText('Light'):'&#9790; '+trText('Dark');
    updateLanguageButton();
    applyDashboardI18n(document.body);
    const obs=new MutationObserver(muts=>{
      if(dashLang!=='zh')return;
      muts.forEach(m=>{
        m.addedNodes&&m.addedNodes.forEach(n=>applyDashboardI18n(n));
        if(m.type==='characterData')i18nNodeText(m.target);
      });
    });
    obs.observe(document.body,{childList:true,subtree:true,characterData:true});
  });
})();

function updateHW4(hw){
  document.querySelectorAll('.hw4-only').forEach(el=>el.classList.toggle('hidden',hw!==2));
}

function clampProfileForHw(hw,sp){
  if(hw===2)return Math.max(0,Math.min(4,Number(sp)||0));
  if(hw===1)return Math.max(0,Math.min(2,Number(sp)||0));
  return 0;
}

function updateProfileControls(hw,sp,spAuto){
  const sp3=$('sp3-group'),sp4=$('sp4-group'),note=$('profile-note');
  const speedSec=$('hw3-speed-section');
  const slewSec=$('hw3-slew-section');
  const safeSp=clampProfileForHw(hw,sp);
  if(sp3)sp3.classList.toggle('hidden',hw!==1);
  if(sp4)sp4.classList.toggle('hidden',hw!==2);
  if(speedSec)speedSec.style.display=hw===1?'':'none';
  if(slewSec)slewSec.style.display=hw===1?'':'none';
  const sp3Seg=$('sp3-seg'),sp4Seg=$('sp4-seg');
  updateProfileSeg(sp3Seg,safeSp,spAuto);
  updateProfileSeg(sp4Seg,safeSp,spAuto);
  if(note){
    if(spAuto)note.textContent='Auto follows the vehicle follow distance.';
    else if(hw===1)note.textContent='Manual SP3 profile is locked.';
    else if(hw===2)note.textContent='Manual SP4 profile is locked.';
    else note.textContent='Profiles are only available on HW3 and HW4.';
  }
}

function updateProfileSeg(el,sp,spAuto){
  if(!el)return;
  el.querySelectorAll('.hw-btn').forEach(b=>{
    const v=parseInt(b.dataset.v);
    b.classList.toggle('active',spAuto?v===-1:v===sp);
  });
}

function updSeg(el,v,cls){
  el.querySelectorAll('.'+cls).forEach(b=>b.classList.toggle('active',parseInt(b.dataset.v)===v));
}

function setHW(v){state.hw=v;state.sp=clampProfileForHw(v,state.sp);updSeg($('hw-seg'),v,'hw-btn');updateHW4(v);updateProfileControls(v,state.sp,state.spAuto);updateSniffIdToggle();renderSniffer();pushCfg();}

function setProfileAuto(){
  state.spAuto=true;
  updateProfileControls(state.hw,state.sp,state.spAuto);
  pushCfg();
}

function setProfile(v){
  state.spAuto=false;
  state.sp=clampProfileForHw(state.hw,v);
  updateProfileControls(state.hw,state.sp,state.spAuto);
  pushCfg();
}

function updateInjectButtons(active){
  const stop=$('btn-stop'),resume=$('btn-resume');
  if(stop)stop.style.display=active?'':'none';
  if(resume)resume.style.display=active?'none':'';
}

function sniffBusPrefix(){return state.hw===0?0x0800:0x1000;}
function sniffBusLabel(){return state.hw===0?'PARTY':'CH';}
function sniffWireId(id){return id&0x7FF;}
function sniffDbcId(id){return sniffWireId(id)|sniffBusPrefix();}
function sniffDisplayId(id){return sniffShowDbcIds?sniffDbcId(id):sniffWireId(id);}
function updateSniffIdToggle(){
  const b=$('sniff-id-btn'),bus=sniffBusLabel();
  b.textContent=sniffShowDbcIds?('DBC '+bus):'Wire IDs';
  b.title=sniffShowDbcIds?('Showing DBC JSON IDs with '+bus+' prefix'):('Showing on-wire 11-bit CAN IDs');
  $('sniff-filter').placeholder='Filter by wire/DBC ID or name';
}
function toggleSniffIdMode(){
  sniffShowDbcIds=!sniffShowDbcIds;
  localStorage.setItem('sniffIdMode',sniffShowDbcIds?'dbc':'wire');
  updateSniffIdToggle();
  renderSniffer();
}

async function pushCfg(){
  const body='hw='+state.hw+'&sp='+state.sp+'&spa='+(state.spAuto?'1':'0')+'&can='+(state.can?'1':'0');
  try{await fetch('/config',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body});}catch(e){}
}

function updateHw3SlewControl(d){
  const enabled=!!d.hw3OffsetSlew;
  const rate=Math.max(1,Math.min(25,parseInt(d.hw3SlewRate,10)||5));
  state.hw3OffsetSlew=enabled;state.hw3SlewRate=rate;
  const tgl=$('hw3-slew-tgl');if(tgl)tgl.checked=enabled;
  const inp=$('hw3-slew-rate');if(inp&&document.activeElement!==inp)inp.value=rate;
  setText('hw3-slew-meta',enabled?('On • '+rate+'%'):'Off');
  setText('hw3-slew-rate-hint',rate+'%/s (about '+(rate*0.6).toFixed(1)+' km/h/s at 60 km/h)');
  setText('hw3-slew-target',d.hw3OffsetTarget===undefined?'0':d.hw3OffsetTarget);
  setText('hw3-slew-last',d.hw3OffsetLast===undefined?'0':d.hw3OffsetLast);
  setText('hw3-slew-count',d.hw3SlewCount||0);
}
async function saveHw3Slew(){
  const tgl=$('hw3-slew-tgl'),inp=$('hw3-slew-rate'),st=$('hw3-slew-status');
  let rate=parseInt(inp.value,10);
  if(isNaN(rate)||rate<1||rate>25){st.textContent='Use 1-25';st.style.color='var(--err)';return;}
  const enabled=tgl.checked?'1':'0';
  st.textContent='Saving...';st.style.color='var(--tx3)';
  try{
    const body='hw3OffsetSlew='+enabled+'&hw3SlewRate='+rate;
    const r=await fetch('/config',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body});
    const d=await r.json();
    if(!d.ok)throw new Error();
    state.hw3OffsetSlew=enabled==='1';state.hw3SlewRate=rate;
    st.textContent='Saved';st.style.color='var(--ok)';
    poll();
  }catch(e){st.textContent='Save failed';st.style.color='var(--err)';}
}

function updateHw3SpeedControl(d){
  const cust=!!d.hw3CustomSpeed,hse=!!d.hw3HighSpeedEnable;
  const enc=parseInt(d.hw3WireEncoding,10)===0?0:1;
  const cTgl=$('hw3-cust-tgl');if(cTgl)cTgl.checked=cust;
  const hTgl=$('hw3-hs-tgl');if(hTgl)hTgl.checked=hse;
  const eSel=$('hw3-enc');if(eSel&&document.activeElement!==eSel)eSel.value=String(enc);
  const ct=Array.isArray(d.hw3CustomTarget)?d.hw3CustomTarget:[];
  for(let i=0;i<5;i++){const el=$('hw3-ct-'+i);if(el&&document.activeElement!==el&&ct[i]!==undefined)el.value=ct[i];}
  const hs=Array.isArray(d.hw3HighSpeedTarget)?d.hw3HighSpeedTarget:[];
  for(let i=0;i<3;i++){const el=$('hw3-hs-'+i);if(el&&document.activeElement!==el&&hs[i]!==undefined)el.value=hs[i];}
  const flags=[];
  if(cust)flags.push('Custom');
  if(hse)flags.push('HighSpd');
  flags.push(enc?'PCT4':'KPH5');
  setText('hw3-speed-meta',(cust||hse)?flags.join(' • '):('Off • '+(enc?'PCT4':'KPH5')));
  const flKph=parseInt(d.fusedSpeedLimitKph,10)||0;
  setText('hw3-fused',flKph?String(flKph)+' km/h':((d.fusedSpeedLimitRaw==31)?'NONE':'SNA'));
  setText('hw3-stock-off',(d.hw3StockOffset===undefined)?'0':String(d.hw3StockOffset)+' km/h');
  setText('hw3-tgt-raw',d.hw3OffsetTarget===undefined?'0':d.hw3OffsetTarget);
}
async function saveHw3Speed(){
  const st=$('hw3-speed-status');
  const cust=$('hw3-cust-tgl').checked?'1':'0';
  const hse=$('hw3-hs-tgl').checked?'1':'0';
  const enc=$('hw3-enc').value==='0'?'0':'1';
  const parts=['hw3CustomSpeed='+cust,'hw3HighSpeedEnable='+hse,'hw3WireEncoding='+enc];
  for(let i=0;i<5;i++){const v=parseInt($('hw3-ct-'+i).value,10);if(!isNaN(v))parts.push('hw3CustomT'+i+'='+Math.max(0,Math.min(160,v)));}
  for(let i=0;i<3;i++){const v=parseInt($('hw3-hs-'+i).value,10);if(!isNaN(v))parts.push('hw3HighTarget'+i+'='+Math.max(0,Math.min(200,v)));}
  st.textContent='Saving...';st.style.color='var(--tx3)';
  try{
    const r=await fetch('/config',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:parts.join('&')});
    const d=await r.json();
    if(!d.ok)throw new Error();
    st.textContent='Saved';st.style.color='var(--ok)';
    poll();
  }catch(e){st.textContent='Save failed';st.style.color='var(--err)';}
}

function updateLegacyMppControl(d){
  const sec=$('legacy-mpp-section');
  if(sec)sec.style.display=(state.hw===0)?'':'none';
  const en=!!d.legacyMppOverride,cust=!!d.legacyMppCustomEnable,hse=!!d.legacyMppHighSpeedEnable;
  const t=$('legacy-mpp-tgl');if(t)t.checked=en;
  const ct=$('legacy-mpp-cust-tgl');if(ct)ct.checked=cust;
  const ht=$('legacy-mpp-hs-tgl');if(ht)ht.checked=hse;
  const cArr=Array.isArray(d.legacyMppCustomTarget)?d.legacyMppCustomTarget:[];
  for(let i=0;i<5;i++){const el=$('legacy-mpp-ct-'+i);if(el&&document.activeElement!==el&&cArr[i]!==undefined)el.value=cArr[i];}
  const hArr=Array.isArray(d.legacyMppHighSpeedTarget)?d.legacyMppHighSpeedTarget:[];
  for(let i=0;i<3;i++){const el=$('legacy-mpp-hs-'+i);if(el&&document.activeElement!==el&&hArr[i]!==undefined)el.value=hArr[i];}
  setText('legacy-mpp-bus-raw',(d.legacyMppLastRaw!==undefined?d.legacyMppLastRaw:0)+(d.legacyMppLastRaw?' ('+(d.legacyMppLastRaw*5)+' km/h)':''));
  setText('legacy-mpp-sent-raw',(d.legacyMppLastSentRaw!==undefined?d.legacyMppLastSentRaw:0)+(d.legacyMppLastSentRaw?' ('+(d.legacyMppLastSentRaw*5)+' km/h)':''));
  const flags=[];
  if(en)flags.push('On');
  if(cust)flags.push('Custom');
  if(hse)flags.push('HighSpd');
  setText('legacy-mpp-meta',flags.length?flags.join(' • '):'Off');
}
async function saveLegacyMpp(){
  const st=$('legacy-mpp-status');
  const en=$('legacy-mpp-tgl').checked?'1':'0';
  const cust=$('legacy-mpp-cust-tgl').checked?'1':'0';
  const hse=$('legacy-mpp-hs-tgl').checked?'1':'0';
  const parts=['legacyMppOverride='+en,'legacyMppCustomEnable='+cust,'legacyMppHighSpeedEnable='+hse];
  for(let i=0;i<5;i++){const v=parseInt($('legacy-mpp-ct-'+i).value,10);if(!isNaN(v))parts.push('legacyMppCustomT'+i+'='+Math.max(0,Math.min(155,v)));}
  for(let i=0;i<3;i++){const v=parseInt($('legacy-mpp-hs-'+i).value,10);if(!isNaN(v))parts.push('legacyMppHighTarget'+i+'='+Math.max(0,Math.min(155,v)));}
  st.textContent='Saving...';st.style.color='var(--tx3)';
  try{
    const r=await fetch('/config',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:parts.join('&')});
    const d=await r.json();
    if(!d.ok)throw new Error();
    st.textContent='Saved';st.style.color='var(--ok)';
    poll();
  }catch(e){st.textContent='Save failed';st.style.color='var(--err)';}
}
function updatePluginReplayControl(count,max){
  count=Math.max(1,parseInt(count,10)||1);
  max=Math.max(count,parseInt(max,10)||20);
  state.plgr=count;state.plgrmax=max;
  const input=$('plugin-replay');
  if(input){input.max=max;if(document.activeElement!==input)input.value=count;}
  const meta=$('plugin-replay-meta');if(meta)meta.textContent=count+'x';
}
async function savePluginReplay(){
  const input=$('plugin-replay'),st=$('plugin-replay-status'),max=state.plgrmax||20;
  let v=parseInt(input.value,10);
  if(isNaN(v)||v<1||v>max){st.textContent='Use 1-'+max;st.style.color='var(--err)';return;}
  st.textContent='Saving...';st.style.color='var(--tx3)';
  try{
    const r=await fetch('/config',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'plgr='+v});
    const d=await r.json();
    if(!d.ok)throw new Error();
    updatePluginReplayControl(v,max);
    st.textContent='Saved';st.style.color='var(--ok)';
    poll();
  }catch(e){st.textContent='Save failed';st.style.color='var(--err)';}
}

function updateApGateControl(d){
  const enabled=!!d.apGate;
  state.apGate=enabled;
  const tgl=$('ap-gate-tgl');if(tgl)tgl.checked=enabled;
  setText('ap-gate-meta',enabled?'On':'Off');
}

function updateForceActivateControl(d){
  const enabled=!!d.force;
  state.force=enabled;
  const tgl=$('force-tgl');if(tgl)tgl.checked=enabled;
  setText('force-meta',enabled?'On':'Off');
}
async function saveForceActivate(){
  const tgl=$('force-tgl'),st=$('force-status');
  const enabled=tgl.checked?'1':'0';
  st.textContent='Saving...';st.style.color='var(--tx3)';
  try{
    const r=await fetch('/config',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'force='+enabled});
    const d=await r.json();
    if(!d.ok)throw new Error();
    state.force=enabled==='1';
    setText('force-meta',state.force?'On':'Off');
    st.textContent='Saved';st.style.color='var(--ok)';
    poll();
  }catch(e){st.textContent='Save failed';st.style.color='var(--err)';}
}
async function saveApGate(){
  const tgl=$('ap-gate-tgl'),st=$('ap-gate-status');
  const enabled=tgl.checked?'1':'0';
  st.textContent='Saving...';st.style.color='var(--tx3)';
  try{
    const r=await fetch('/config',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'apg='+enabled});
    const d=await r.json();
    if(!d.ok)throw new Error();
    state.apGate=enabled==='1';
    setText('ap-gate-meta',state.apGate?'On':'Off');
    st.textContent='Saved';st.style.color='var(--ok)';
    poll();
  }catch(e){st.textContent='Save failed';st.style.color='var(--err)';}
}

async function pushLogging(){
  const body='eprn='+($('tgl-eprn').checked?'1':'0');
  try{await fetch('/logging',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body});}catch(e){}
  if($('tgl-eprn').checked)pollLog();
  poll();
}

async function emergencyStop(){if(!await dashConfirm('Stop injecting? This remains disabled after reboot until you press Resume Injection.','Stop injection','Stop'))return;try{await fetch('/disable',{method:'POST'});}catch(e){}poll();}
async function resumeInj(){try{await fetch('/config',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'hw='+state.hw+'&sp='+state.sp+'&spa='+(state.spAuto?'1':'0')+'&can=1'});}catch(e){}poll();}
async function reboot(){if(!await dashConfirm('Reboot device?','Reboot','Reboot'))return;try{await fetch('/reboot',{method:'POST'});}catch(e){}}

function fmtUp(s){
  if(s<60)return s+'s';
  if(s<3600)return Math.floor(s/60)+'m '+String(s%60).padStart(2,'0')+'s';
  return Math.floor(s/3600)+'h '+Math.floor((s%3600)/60)+'m';
}
function fmtBytes(n){
  n=Number(n)||0;
  if(n>=1048576)return (n/1048576).toFixed(n>=10485760?1:2)+' MB';
  if(n>=1024)return (n/1024).toFixed(n>=10240?0:1)+' KB';
  return n+' B';
}
function pct(used,total){
  total=Number(total)||0;used=Number(used)||0;
  return total>0?Math.max(0,Math.min(100,used*100/total)):0;
}
function setFill(id,value){
  const el=$(id);if(el)el.style.width=Math.max(0,Math.min(100,value||0))+'%';
}
function resetSystemStatusUi(){
  ['sys-chip','sys-cpu','sys-board','sys-temp','sys-reset','sys-heap','sys-largest','sys-minheap','sys-psram','sys-tasks','sys-flash','sys-spiffs','sys-rssi','sys-wifi-mode','sys-apclients','sys-ble','sys-wireless','sys-fw'].forEach(id=>setText(id,'--'));
  setText('sys-summary',trText('Monitoring off'));
  setText('sys-cpu-load',trText('off'));
  ['sys-cpu0-fill','sys-cpu1-fill','sys-heap-fill','sys-app-fill','sys-spiffs-fill'].forEach(id=>setFill(id,0));
}
function startSystemMonitor(){
  if(systemStatusEnabled)return;
  systemStatusEnabled=true;
  const t=$('sys-monitor-tgl');if(t)t.checked=true;
  loadSystemStatus();
  systemStatusTimer=setInterval(loadSystemStatus,1000);
}
function stopSystemMonitor(){
  systemStatusEnabled=false;
  const t=$('sys-monitor-tgl');if(t)t.checked=false;
  if(systemStatusTimer){clearInterval(systemStatusTimer);systemStatusTimer=null;}
  resetSystemStatusUi();
}
function toggleSystemMonitor(){
  const t=$('sys-monitor-tgl');
  if(t&&t.checked)startSystemMonitor();else stopSystemMonitor();
}
function initSystemMonitor(){
  stopSystemMonitor();
}
async function loadSystemStatus(){
  if(!systemStatusEnabled)return;
  return runPoll('system_status',async()=>{
    try{
      const d=await fetchPollJson('/system_status',2500);
      const heapUsed=(d.heap_total||0)-(d.heap_free||0);
      const appUsed=d.app_used||0;
      const spiffsUsed=d.spiffs_used||0;
      setText('sys-summary',(d.module||d.chip||'ESP32')+' • '+(d.cores||'?')+' cores • '+(d.cpu_mhz||'?')+' MHz now');
      setText('sys-chip',(d.module||d.chip||'?')+' rev '+(d.revision===undefined?'?':d.revision)+' / '+(d.target||''));
      setText('sys-cpu',(d.cores||'?')+' cores • now '+(d.cpu_mhz||'?')+' MHz • max '+(d.cpu_max_mhz||240)+' MHz');
      if(d.cpu_load_valid){
        setText('sys-cpu-load','CPU0 '+(d.cpu0_load||0)+'% • CPU1 '+(d.cpu1_load||0)+'%');
        setFill('sys-cpu0-fill',d.cpu0_load||0);setFill('sys-cpu1-fill',d.cpu1_load||0);
      }else{
        setText('sys-cpu-load',trText('warming up'));
        setFill('sys-cpu0-fill',0);setFill('sys-cpu1-fill',0);
      }
      setText('sys-board','SRAM '+fmtBytes(d.sram_bytes)+' + RTC '+fmtBytes(d.rtc_sram_bytes)+' • ROM '+fmtBytes(d.rom_bytes));
      setText('sys-temp',d.temp_c===null||d.temp_c===undefined?trText('unavailable'):(Number(d.temp_c).toFixed(1)+' °C'));
      setText('sys-reset',d.reset||'?');
      setText('sys-heap',fmtBytes(d.heap_free)+' free / '+fmtBytes(d.heap_total)+' total');
      setText('sys-largest',fmtBytes(d.heap_largest));
      setText('sys-minheap',fmtBytes(d.heap_min));
      setText('sys-psram',(d.psram_total||0)?(fmtBytes(d.psram_free)+' free / '+fmtBytes(d.psram_total)+' total'):trText('not enabled'));
      setText('sys-tasks',(d.tasks||'?')+' tasks');
      setText('sys-flash',fmtBytes(d.flash_size)+' flash • app '+(d.app_label||'?')+' '+fmtBytes(appUsed||d.app_size)+' / '+fmtBytes(d.app_size));
      setText('sys-spiffs',d.spiffs_ok?(fmtBytes(spiffsUsed)+' used / '+fmtBytes(d.spiffs_total)):'SPIFFS '+trText('unavailable'));
      setText('sys-rssi',d.wifi_rssi===null||d.wifi_rssi===undefined?(d.wifi_connected?'?':'offline'):(d.wifi_rssi+' dBm'));
      setText('sys-wifi-mode',(d.wifi_mode||'?')+' • '+(d.wifi_connected?trText('STA online'):trText('STA offline'))+' • sleep '+(d.wifi_sleep?trText('on'):trText('off')));
      setText('sys-apclients',(d.ap_clients||0)+' client'+((d.ap_clients||0)===1?'':'s'));
      setText('sys-ble',(d.ble_supported?trText('supported'):trText('not supported'))+' • '+(d.ble_enabled?trText('enabled'):trText('firmware disabled')));
      setText('sys-wireless',(d.wifi_standard||'2.4GHz Wi-Fi')+' • '+(d.wifi_max_mbps||150)+' Mbps max • BLE 5 LE');
      setText('sys-fw',(d.mac||'--')+' • '+(d.firmware||'unknown')+' • IDF '+(d.idf||'?'));
      setFill('sys-heap-fill',pct(heapUsed,d.heap_total));
      setFill('sys-app-fill',appUsed?pct(appUsed,d.app_size):0);
      setFill('sys-spiffs-fill',pct(spiffsUsed,d.spiffs_total));
    }catch(e){
      setText('sys-summary','System status unavailable');
    }
  });
}
function fmtAgeMs(ms){
  if(ms<1000)return ms+' ms';
  if(ms<10000)return (ms/1000).toFixed(1)+' s';
  if(ms<60000)return Math.round(ms/1000)+' s';
  return fmtUp(Math.floor(ms/1000));
}
function toHex(n,p){return n.toString(16).toUpperCase().padStart(p,'0')}
function fmtProbeData(data,dlc){
  if(!Array.isArray(data)||!dlc)return '—';
  return data.slice(0,dlc).map(v=>toHex((v||0)&255,2)).join(' ');
}
function renderWriteProbe(p){
  const status=$('probe-status');
  if(!p||!p.active){
    status.textContent='No injected frame yet';
    status.className='probe-status v-dim';
    $('probe-tx-meta').textContent='—';
    $('probe-tx').textContent='—';
    $('probe-rx-meta').textContent='—';
    $('probe-rx').textContent='—';
    return;
  }
  const id='CAN 0x'+toHex((p.id||0)&0x7FF,3)+(p.mux>=0?' · mux '+p.mux:'');
  $('probe-tx-meta').textContent=id+' · '+fmtAgeMs(p.txa||0)+' ago';
  $('probe-tx').textContent=fmtProbeData(p.tx,p.txdlc);
  if(p.hasrx){
    $('probe-rx-meta').textContent=id+' · '+fmtAgeMs(p.rxa||0)+' ago';
    $('probe-rx').textContent=fmtProbeData(p.rx,p.rxdlc);
  }else{
    $('probe-rx-meta').textContent='No matching RX frame seen yet';
    $('probe-rx').textContent='—';
  }
  let text='Waiting for next matching bus frame';
  let cls='probe-status v-acc';
  if(p.state===2){text='Matching frame seen on bus';cls='probe-status v-ok';}
  else if(p.state===3){text='Latest bus frame differs from injected frame';cls='probe-status v-warn';}
  else if(p.state===4){text='Driver transmit failed';cls='probe-status v-err';}
  status.textContent=text;
  status.className=cls;
}

function renderEflg(e){
  const el=$('eflg-row');
  if(!e){el.innerHTML='<span class="eflg-pill eflg-ok">OK</span>';return;}
  let h='';
  if(e&0x20)h+='<span class="eflg-pill eflg-err">Bus-Off</span>';
  if(e&0x10)h+='<span class="eflg-pill eflg-warn">TX Passive</span>';
  if(e&0x08)h+='<span class="eflg-pill eflg-warn">RX Passive</span>';
  if(e&0x04)h+='<span class="eflg-pill eflg-warn">TX Warn</span>';
  if(e&0x02)h+='<span class="eflg-pill eflg-warn">RX Warn</span>';
  if(e&0xC0)h+='<span class="eflg-pill eflg-err">RX Overflow</span>';
  el.innerHTML=h||'<span class="eflg-pill eflg-ok">OK</span>';
}

function togglePause(){
  sniffPaused=!sniffPaused;
  syncSniffPauseButton();
  renderSniffer();
}

function renderSniffer(){
  updateSniffIdToggle();
  const filter=$('sniff-filter').value.trim().toLowerCase();
  const el=$('sniffer');
  let frames=sniffFrames;
  if(filter){
    const fid=parseInt(filter);
    if(!isNaN(fid))frames=frames.filter(f=>sniffWireId(f.id)===fid||sniffDbcId(f.id)===fid);
    else frames=frames.filter(f=>f.name&&f.name.toLowerCase().includes(filter));
  }
  $('sniff-count').textContent=frames.length+' frames';
  if(!frames.length){
    el.innerHTML='<div style="padding:20px;color:var(--tx3);text-align:center;font-size:12px">'+(sniffPaused?'Sniffer paused':'No frames')+'</div>';
    return;
  }
  const ADIds=new Set([1021,1016,921]);
  el.innerHTML=frames.slice(-30).reverse().map(f=>{
    const hex=Array.from({length:f.dlc},(_,i)=>toHex(f.data[i],2)).join(' ');
    const wireId=sniffWireId(f.id),dbcId=sniffDbcId(f.id),displayId=sniffDisplayId(f.id);
    const altId=sniffShowDbcIds?('Wire 0x'+toHex(wireId,3)):('DBC '+sniffBusLabel()+' 0x'+toHex(dbcId,3));
    return`<div class="sniff-row${ADIds.has(f.id)?' hi':''}">
      <span class="s-ts">${(f.ts/1000).toFixed(1)}s</span>
      <span class="s-id" title="${altId}">0x${toHex(displayId,3)}</span>
      <div><div class="s-data">${hex}</div>${f.name?`<div class="s-name">${f.name}</div>`:''}</div>
    </div>`;
  }).join('');
}

async function pollSniffer(){
  return runPoll('frames',async()=>{
    if(sniffPaused||!dashboardStatusOk)return;
    try{const d=await fetchPollJson('/frames',2500);sniffFrames=d.frames||[];renderSniffer();}catch(e){}
  });
}

// OTA upload
function fileSelected(file){
  if(!file)return;
  otaFile=file;
  const drop=$('ota-drop');
  drop.querySelector('.ota-text').textContent=file.name;
  drop.querySelector('.ota-sub').textContent=(file.size/1024).toFixed(0)+' KB';
  $('ota-upload-btn').style.display='block';
}

function handleDrop(e){
  e.preventDefault();
  $('ota-drop').classList.remove('drag');
  const file=e.dataTransfer.files[0];
  if(file&&file.name.endsWith('.bin'))fileSelected(file);
}

function resetOtaCredentials(){
  localStorage.removeItem('otaU');
  localStorage.removeItem('otaP');
  otaUser='';
  otaPass='';
  const btn=$('ota-reset-btn');
  if(btn){
    btn.textContent='OTA Credentials Reset';
    setTimeout(()=>{btn.textContent='Reset OTA Credentials';},1500);
  }
}

async function uploadFirmware(){
  if(!otaFile)return;
  if(!otaUser){otaUser=prompt('OTA Username:')||'';localStorage.setItem('otaU',otaUser);}
  if(!otaPass){otaPass=prompt('OTA Password:')||'';localStorage.setItem('otaP',otaPass);}
  if(!otaUser||!otaPass)return;
  const prog=$('ota-progress');
  const fill=$('ota-fill');
  const status=$('ota-status');
  prog.style.display='block';
  $('ota-upload-btn').disabled=true;
  $('ota-upload-btn').textContent='Flashing...';

  const xhr=new XMLHttpRequest();
  xhr.upload.onprogress=e=>{
    if(e.lengthComputable){
      const pct=Math.round(e.loaded/e.total*100);
      fill.style.width=pct+'%';
      status.textContent='Uploading... '+pct+'%';
    }
  };
  xhr.onload=()=>{
    if(xhr.status===200){
      status.textContent='Done! Device is rebooting...';
      fill.style.width='100%';
      setTimeout(()=>window.location.reload(),5000);
    } else {
      status.textContent='Upload failed: '+xhr.status;
      status.style.color='var(--err)';
    }
    $('ota-upload-btn').disabled=false;
    $('ota-upload-btn').textContent='Flash Firmware';
  };
  xhr.onerror=()=>{
    status.textContent='Connection error';
    status.style.color='var(--err)';
    $('ota-upload-btn').disabled=false;
  };
  xhr.open('POST','/update',true,otaUser,otaPass);
  xhr.setRequestHeader('X-File-Name',otaFile.name);
  xhr.setRequestHeader('X-File-Size',otaFile.size);
  const form=new FormData();
  form.append('firmware',otaFile);
  xhr.send(form);
}

async function poll(){
  return runPoll('status',async()=>{
    try{
      const d=await fetchPollJson('/status',5000,true);
    const on=!!d.can,armed=!!d.ci,injecting=typeof d.ia==='undefined'?armed:!!d.ia,fpsVal=Number(d.fps||0);
    state.hw=d.hw;state.sp=clampProfileForHw(d.hw,d.sp);state.spAuto=typeof d.spAuto==='undefined'?state.spAuto:!!d.spAuto;state.can=armed;
    if(typeof d.plgr!=='undefined')updatePluginReplayControl(d.plgr,d.plgrmax);
    if(typeof d.force!=='undefined')updateForceActivateControl(d);
    if(typeof d.apGate!=='undefined')updateApGateControl(d);
    updateHw3SlewControl(d);
    updateHw3SpeedControl(d);
    updateLegacyMppControl(d);
    setClass('dot','sdot '+(d.txerr>5?'dot-warn':on?'dot-on':'dot-off'));
    const apActive=typeof d.apActive==='undefined'?!!d.AD:!!d.apActive;
    const adEnabled=typeof d.adEnabled==='undefined'?false:!!d.adEnabled;
    setText('hdr-desc',on?(injecting?(apActive?'AP active — injecting':(adEnabled?'FSD requested — injecting':'CAN active — injecting')):(armed&&d.apGate?'Waiting for AP — injection armed':'CAN active — monitoring')):'Waiting for CAN frames');
    updateInjectButtons(armed);

    setText('s-can',on?'Active':'Offline');
    setClass('s-can','stat-val '+(on?'v-ok':'v-err'));
    setText('s-inj',injectionStatusLabel(injecting,armed,d.apGate,d));
    setClass('s-inj','stat-val '+(injecting?'v-ok':(armed&&d.apGate?'v-warn':'v-err')));
    setText('s-AD',apActive?'Active':'Inactive');
    setClass('s-AD','stat-val '+(apActive?'v-ok':'v-dim'));
    setText('s-fps',fpsVal.toFixed(1)+' Hz');
    setClass('s-fps','stat-val '+(fpsVal>5?'v-acc':'v-dim'));
    setText('s-rx',d.rx);
    setText('s-tx',d.tx);
    setText('s-txerr',d.txerr);
    setClass('s-txerr','stat-val '+(d.txerr>0?'v-warn':'v-dim'));
    setText('s-fd',d.fd||'—');
    setText('s-prof',profileDisplayName(d.hw,state.sp,state.spAuto));
    setText('s-soff',d.soff||'0');
    setText('s-up',fmtUp(d.up));
    setText('s-mcp-raw','EFLG: 0x'+toHex(d.eflg,2));
    const fpsFill=$('fps-fill');if(fpsFill)fpsFill.style.width=Math.min(fpsVal/20*100,100)+'%';
    setText('hw-badge',HW[d.hw]||'?');
    updateGtwBadge(d.gtwap);
    try{renderEflg(d.eflg);}catch(e){}
    try{renderWriteProbe(d.probe);}catch(e){}
    if(d.mux){for(let i=0;i<3;i++){setText('m'+i+'rx',d.mux[i].rx);setText('m'+i+'tx',d.mux[i].tx);const e=$('m'+i+'err');if(e){e.textContent=d.mux[i].err;e.style.color=d.mux[i].err>0?'var(--err)':'';}}}
    updateSniffIdToggle();
    const hwSeg=$('hw-seg');if(hwSeg)updSeg(hwSeg,d.hw,'hw-btn');updateHW4(d.hw);updateProfileControls(d.hw,state.sp,state.spAuto);
    const eprn=$('tgl-eprn');if(eprn&&typeof d.eprn!=='undefined')eprn.checked=d.eprn;
    if(!dashboardInitialLoaded){
      dashboardInitialLoaded=true;
      loadWifiNetworks();loadWifiStatus();loadApStatus();loadCanPins();loadGatewayDns();loadGatewayStatus();loadGatewayBlocked();
      if(canDebugEnabled)startCanDebugPolling();
    }
    }catch(e){}
  });
}

function colorLog(l){
  if(l.includes('AD=ON')||l.includes('AD active'))return'<span class="lf">'+l+'</span>';
  if(l.match(/\[HW[34]\]|\[LEGACY\]|\[HW3\]/))return'<span class="lh">'+l+'</span>';
  if(l.includes('ERR')||l.includes('FAIL'))return'<span class="le">'+l+'</span>';
  if(l.includes('[CFG]'))return'<span class="lc">'+l+'</span>';
  if(l.includes('[OK]')||l.includes('[BOOT]'))return'<span class="lf">'+l+'</span>';
  if(l.includes('[OTA]'))return'<span class="lo">'+l+'</span>';
  return l;
}
async function pollLog(){
  return runPoll('log',async()=>{
    if(!$('tgl-eprn').checked||!dashboardStatusOk)return;
    try{
      const d=await fetchPollJson('/log?since='+logSince,2000);
    if(d.seq)logSince=d.seq;
    if(!d.lines.length)return;
    const el=$('log');
    const newHtml=d.lines.map(colorLog).join('\n');
    if(el.textContent==='Waiting...'||el.textContent==='等待中...'||!el.dataset.logSeen)el.innerHTML=newHtml,el.dataset.logSeen='1';
    else el.innerHTML+='\n'+newHtml;
    // trim to 100 lines
    const lines=el.innerHTML.split('\n');
    if(lines.length>100)el.innerHTML=lines.slice(-100).join('\n');
    el.scrollTop=el.scrollHeight;
    }catch(e){}
  });
}

async function resetStats(){try{await fetch('/reset_stats',{method:'POST'});}catch(e){}poll();}

let recIsActive=false,recInterval=null;
async function toggleRec(){recIsActive?await stopRec():await startRec();}
async function startRec(){
  try{
    await fetch('/rec_start',{method:'POST'});
    recIsActive=true;
    const b=$('rec-btn');
    b.textContent='Stop Recording';
    b.style.borderColor='var(--err)';b.style.color='var(--err)';
    $('rec-dl').style.display='none';
    recInterval=setInterval(pollRec,800);
  }catch(e){}
}
async function stopRec(){
  clearInterval(recInterval);recIsActive=false;
  try{await fetch('/rec_stop',{method:'POST'});}catch(e){}
  const b=$('rec-btn');
  b.textContent='Start Recording';b.style.borderColor='';b.style.color='';
  await pollRec();
}
async function pollRec(){
  try{
    const d=await(await fetch('/rec_status')).json();
    const pct=Math.min(d.count/d.cap*100,100);
    $('rec-fill').style.width=pct+'%';
    $('rec-count').textContent=d.count+' / '+d.cap+' frames';
    if(d.active){
      $('rec-status').textContent='Recording...';$('rec-status').style.color='var(--err)';
      $('rec-meta').textContent='Recording...';
    } else {
      $('rec-meta').textContent=d.saved?d.count+' frames saved':'Idle';
      $('rec-status').textContent=d.saved?'Saved':'Ready';
      $('rec-status').style.color=d.saved?'var(--ok)':'';
      $('rec-dl').style.display=d.saved?'':'none';
      if(recIsActive){recIsActive=false;clearInterval(recInterval);const b=$('rec-btn');b.textContent='Start Recording';b.style.borderColor='';b.style.color='';}
    }
  }catch(e){}
}

// ── AP Hotspot management ──
async function saveAP(){
  const ssid=$('ap-ssid').value,pass=$('ap-pass').value,hidden=$('ap-hidden').checked?'1':'0';
  if(!ssid){$('ap-status').textContent='Enter hotspot name';$('ap-status').style.color='var(--err)';return;}
  if(pass&&pass.length<8){$('ap-status').textContent='Password min 8 chars';$('ap-status').style.color='var(--err)';return;}
  try{const r=await fetch('/ap_config',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'ssid='+encodeURIComponent(ssid)+'&pass='+encodeURIComponent(pass)+'&hidden='+hidden});
    const d=await r.json();
    if(d.ok){$('ap-status').textContent='Saved! Reboot to apply.';$('ap-status').style.color='var(--ok)';$('ap-pass').value='';}
    else{$('ap-status').textContent=d.error||'Error';$('ap-status').style.color='var(--err)';}
  }catch(e){$('ap-status').textContent='Error';$('ap-status').style.color='var(--err)';}
}
async function loadApStatus(){
  return runPoll('ap_status',async()=>{
    if(!dashboardStatusOk)return;
    try{const d=await fetchPollJson('/ap_status',2000);
    if(d.ssid)$('ap-ssid').value=d.ssid;
    $('ap-clients').textContent=d.clients+' client'+(d.clients!==1?'s':'');
    if(typeof d.hidden!=='undefined')$('ap-hidden').checked=!!d.hidden;
    if(d.stored){$('ap-stored').textContent='saved';$('ap-stored').style.color='var(--ok)';}
    else{$('ap-stored').textContent='firmware default';$('ap-stored').style.color='var(--tx3)';}
    }catch(e){}
  });
}
// ── WiFi management ──
function toggleStaticIP(){
  $('static-fields').style.display=$('wifi-static').checked?'block':'none';
}
function rssiIcon(r){
  if(r>=-50) return '\u2587\u2587\u2587\u2587';
  if(r>=-60) return '\u2587\u2587\u2587\u2581';
  if(r>=-70) return '\u2587\u2587\u2581\u2581';
  return '\u2587\u2581\u2581\u2581';
}
async function scanWifi(){
  $('scan-btn').textContent='Scanning...';$('scan-btn').disabled=true;
  try{
    const r=await fetch('/wifi_scan');const d=await r.json();
    const el=$('wifi-nets');
    if(!d.networks.length){el.innerHTML='<div style="padding:8px;font-size:11px;color:var(--tx3);text-align:center">No networks found</div>';el.style.display='block';}
    else{el.innerHTML=d.networks.map(n=>'<div onclick="pickWifi(\''+n.ssid.replace(/'/g,"\\'")+'\')" style="padding:6px 10px;cursor:pointer;display:flex;justify-content:space-between;align-items:center;border-bottom:1px solid var(--bd);font-size:12px" onmouseover="this.style.background=\'var(--bg)\'" onmouseout="this.style.background=\'\'"><span>'+(n.enc?'\uD83D\uDD12 ':'')+n.ssid+'</span><span style="color:var(--tx3);font-size:10px">'+rssiIcon(n.rssi)+' '+n.rssi+'dBm CH'+n.ch+'</span></div>').join('');el.style.display='block';}
  }catch(e){$('wifi-status').textContent='Scan failed';$('wifi-status').style.color='var(--err)';}
  $('scan-btn').textContent='Scan';$('scan-btn').disabled=false;
}
function pickWifi(ssid){
  $('wifi-ssid').value=ssid;$('wifi-nets').style.display='none';$('wifi-pass').focus();
}
let wifiSlotCache={count:0,max:4,active:-1,networks:[]};
let wifiStatusCache={};
function escapeHtml(s){return String(s||'').replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;').replace(/"/g,'&quot;').replace(/'/g,'&#39;');}
function renderWifiSlots(){
  const list=$('wifi-saved-list'),wrap=$('wifi-add-wrap'),cnt=$('wifi-slot-count');
  if(!list)return;
  const nets=wifiSlotCache.networks||[];
  const max=wifiSlotCache.max||4;
  const active=wifiSlotCache.active;
  cnt.textContent='('+nets.length+'/'+max+')';
  if(!nets.length){
    list.innerHTML='<div style="font-size:11px;color:var(--tx3);padding:6px 0">No networks saved.</div>';
  }else{
    list.innerHTML=nets.map(n=>{
      const isActive=n.idx===active;
      const dot='<span style="display:inline-block;width:8px;height:8px;border-radius:50%;background:'+(isActive?'var(--ok)':'var(--tx3)')+';margin-right:6px"></span>';
      const tag=n.static?'<span style="font-size:10px;color:var(--tx3);margin-left:6px">[static]</span>':'';
      return '<div style="display:flex;align-items:center;gap:6px;padding:6px 0;border-bottom:1px solid var(--bd);font-size:12px">'+
        '<div style="flex:1;min-width:0;overflow:hidden;text-overflow:ellipsis;white-space:nowrap">'+dot+escapeHtml(n.ssid)+tag+'</div>'+
        '<button class="sniff-btn" onclick="editWifiSlot('+n.idx+')" style="padding:4px 8px;font-size:11px">Edit</button>'+
        '<button class="sniff-btn" onclick="deleteWifiSlot('+n.idx+')" style="padding:4px 8px;font-size:11px;background:var(--errBg);border-color:var(--errBd);color:var(--err)">Delete</button>'+
      '</div>';
    }).join('');
  }
  const editIdx=parseInt($('wifi-edit-idx').value,10);
  const canAdd=nets.length<max||editIdx>=0;
  wrap.style.display=canAdd?'':'none';
    $('wifi-save-btn').textContent=trText(editIdx>=0?'Save Changes':'Save & Connect');
}
async function loadWifiNetworks(){
  return runPoll('wifi_networks',async()=>{
    try{
      const d=await fetchPollJson('/wifi_networks',2000);
      wifiSlotCache=d;
      renderWifiSlots();
    }catch(e){}
  });
}
async function loadWifiStatus(){
  return runPoll('wifi_status',async()=>{
    try{const d=await fetchPollJson('/wifi_status',2000);
    wifiStatusCache=d;
    dashboardStaIp=d.connected&&d.ip?d.ip:'';
    if(typeof d.active==='number')wifiSlotCache.active=d.active;
    renderWifiSlots();
    if(d.connected){
      setText('wifi-status',(d.ip&&d.ip!==location.hostname)?('Connected: '+(d.ssid||'')+' \u2022 '+d.ip+' \u2022 switch to that WiFi and open this IP'):('Connected: '+(d.ssid||'')+' \u2022 '+d.ip));
      $('wifi-status').style.color='var(--ok)';
    }
    else if(d.connecting&&d.ssid){
      setText('wifi-status','Connecting to '+d.ssid+'...');$('wifi-status').style.color='var(--acc)';
    }
    else if(d.count>0){
      setText('wifi-status',d.count+' saved \u2022 trying to connect...');
      $('wifi-status').style.color='var(--tx3)';
    }
    else{
      setText('wifi-status','Not configured');
      $('wifi-status').style.color='var(--tx3)';
    }
    }catch(e){}
  });
}
function editWifiSlot(idx){
  const n=(wifiSlotCache.networks||[]).find(x=>x.idx===idx);
  if(!n)return;
  $('wifi-edit-idx').value=idx;
  $('wifi-ssid').value=n.ssid;
  $('wifi-pass').value='';
  $('wifi-pass').placeholder='Leave empty to keep current';
  $('wifi-static').checked=!!n.static;
  toggleStaticIP();
  if(n.static){
    $('wifi-ip').value=n.ip||'';
    $('wifi-gw').value=n.gw||'';
    $('wifi-mask').value=n.mask||'255.255.255.0';
    $('wifi-dns').value=n.dns||'';
  }
  renderWifiSlots();
  $('wifi-add-wrap').scrollIntoView({behavior:'smooth',block:'nearest'});
}
function clearWifiForm(){
  $('wifi-edit-idx').value=-1;
  $('wifi-ssid').value='';$('wifi-pass').value='';
  $('wifi-pass').placeholder='Password';
  $('wifi-static').checked=false;toggleStaticIP();
  $('wifi-ip').value='';$('wifi-gw').value='';$('wifi-mask').value='255.255.255.0';$('wifi-dns').value='';
}
async function deleteWifiSlot(idx){
  const n=(wifiSlotCache.networks||[]).find(x=>x.idx===idx);
  if(!n)return;
  if(!await dashConfirm('Delete network "'+n.ssid+'"?','Delete WiFi','Delete'))return;
  try{
    await fetch('/wifi_delete',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'idx='+idx});
    if(parseInt($('wifi-edit-idx').value,10)===idx)clearWifiForm();
    loadWifiNetworks();loadWifiStatus();
  }catch(e){$('wifi-status').textContent='Delete failed';$('wifi-status').style.color='var(--err)';}
}
async function saveWifi(){
  const ssid=$('wifi-ssid').value,pass=$('wifi-pass').value;
  if(!ssid){$('wifi-status').textContent='Enter SSID';$('wifi-status').style.color='var(--err)';return;}
  const editIdx=parseInt($('wifi-edit-idx').value,10);
  const isEdit=editIdx>=0;
  if(!isEdit&&(wifiSlotCache.count||0)>=(wifiSlotCache.max||4)){
    $('wifi-status').textContent='Max '+(wifiSlotCache.max||4)+' networks';$('wifi-status').style.color='var(--err)';return;
  }
  let effectivePass=pass;
  if(isEdit&&!pass){
    const orig=(wifiSlotCache.networks||[]).find(x=>x.idx===editIdx);
    if(orig&&!orig.hasPass)effectivePass='';
    else if(!pass){$('wifi-status').textContent='Password required';$('wifi-status').style.color='var(--err)';return;}
  }
  let body='ssid='+encodeURIComponent(ssid)+'&pass='+encodeURIComponent(effectivePass);
  if(isEdit)body+='&idx='+editIdx;
  if($('wifi-static').checked){
    body+='&static=1&ip='+encodeURIComponent($('wifi-ip').value)+'&gw='+encodeURIComponent($('wifi-gw').value)+'&mask='+encodeURIComponent($('wifi-mask').value)+'&dns='+encodeURIComponent($('wifi-dns').value);
  }
  try{
    const r=await fetch('/wifi_config',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body});
    const d=await r.json();
    if(!d.ok)throw new Error(d.error||'save failed');
    $('wifi-status').textContent='Connecting to '+ssid+'...';$('wifi-status').style.color='var(--acc)';
    clearWifiForm();
    loadWifiNetworks();
    setTimeout(loadWifiStatus,500);
    setTimeout(loadWifiStatus,2500);
    setTimeout(loadWifiStatus,5500);
  }catch(e){$('wifi-status').textContent=e.message||'Error';$('wifi-status').style.color='var(--err)';}
}
// ── STA-AP Gateway / DNS ──
let gatewayMode=1;
function setGatewayMode(mode,persist){
  gatewayMode=mode?1:0;
  const b=$('gw-mode-black'),w=$('gw-mode-white');
  if(b&&w){
    b.classList.toggle('active',gatewayMode===0);
    w.classList.toggle('active',gatewayMode===1);
    b.setAttribute('aria-pressed',gatewayMode===0?'true':'false');
    w.setAttribute('aria-pressed',gatewayMode===1?'true':'false');
  }
  const hint=$('gw-mode-hint');
  if(hint){
    hint.textContent=(gatewayMode===0?'Current: Blacklist mode':'Current: Whitelist mode')+(persist?' - saving automatically':' - click mode to save immediately');
    hint.style.color=persist?'var(--acc)':'var(--tx3)';
  }
  if(persist)saveGatewayDns().catch(()=>{});
}
async function loadGatewayStatus(){
  return runPoll('gateway_status',async()=>{
    try{
      const d=await fetchPollJson('/gateway_status',2000);
      if(!$('gw-status'))return;
      var statusText=(d.enabled?'Enabled':'Disabled')+' \u2022 NAT '+(d.nat?'on':'waiting')+' \u2022 blocked '+(d.blocked||0);
      if(d.strict)statusText+=' \u2022 strict (allow '+(d.allowed_ips||0)+' / block '+(d.blocked_ips||0)+')';
      $('gw-status').textContent=statusText;
      $('gw-status').style.color=d.enabled?(d.nat?'var(--ok)':'var(--acc)'):'var(--tx3)';
      var sp=$('gw-strict-panel');if(sp)sp.style.display=d.strict?'block':'none';
      var ss=$('gw-strict-stats');if(ss)ss.textContent='allowed '+(d.allowed_ips||0)+' \u2022 blocked '+(d.blocked_ips||0);
    }catch(e){
      if($('gw-status')){$('gw-status').textContent='Gateway not available';$('gw-status').style.color='var(--tx3)';}
    }
  });
}
async function loadGatewayDns(){
  try{
    const r=await fetch('/gateway_dns');if(!r.ok)throw new Error('unavailable');
    const d=await r.json();
    if(!$('gw-enabled'))return;
    $('gw-enabled').checked=!!d.enabled;
    $('gw-strict').checked=!!d.strict;
    $('gw-blacklist').value=d.blacklist||'';
    $('gw-whitelist').value=d.whitelist||'';
    setGatewayMode(d.mode||0);
    var ce=$('gw-list-counts');
    if(ce){
      var bc=d.black_count||0,bm=d.black_max||100,wc=d.white_count||0,wm=d.white_max||200;
      ce.textContent='Whitelist '+wc+'/'+wm+' • Blacklist '+bc+'/'+bm;
      ce.style.color=(wc>=wm||bc>=bm)?'var(--err)':'var(--tx3)';
    }
  }catch(e){}
}
async function saveGatewayDns(){
  const msg=$('gw-msg');
  try{
    if(msg){msg.textContent='Saving...';msg.style.color='var(--tx3)';}
    document.querySelectorAll('.gateway-mode-btn').forEach(el=>el.classList.add('saving'));
    const body='enabled='+($('gw-enabled').checked?1:0)+'&mode='+gatewayMode+'&strict='+($('gw-strict').checked?1:0)+'&blacklist='+encodeURIComponent($('gw-blacklist').value)+'&whitelist='+encodeURIComponent($('gw-whitelist').value);
    const r=await fetch('/gateway_dns',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body});
    if(!r.ok)throw new Error('save failed');
    if(msg){msg.textContent='Saved';msg.style.color='var(--ok)';}
    const hint=$('gw-mode-hint');
    if(hint){hint.textContent=(gatewayMode===0?'Current: Blacklist mode':'Current: Whitelist mode')+' - saved';hint.style.color='var(--ok)';}
    loadGatewayDns();loadGatewayStatus();loadGatewayBlocked();
  }catch(e){if(msg){msg.textContent=e.message||'Error';msg.style.color='var(--err)';}}
  finally{document.querySelectorAll('.gateway-mode-btn').forEach(el=>el.classList.remove('saving'));}
}
function openGwBlockedModal(){loadGatewayBlocked();}
function closeGwBlockedModal(){}
function gwBlockedBackdrop(e){}
async function loadGatewayBlocked(){
  const list=$('gw-blocked-list');
  const sum=$('gw-blocked-summary');
  if(!list)return;
  try{
    const r=await fetch('/gateway_blocked');if(!r.ok)throw new Error('HTTP '+r.status);
    const d=await r.json();
    if(sum)sum.textContent=trText('Only non-blacklist domains can be added to the whitelist.')+' - '+(d.length||0)+' '+trText('items');
    if(!d.length){list.innerHTML='<div style="color:var(--tx3);text-align:center;padding:20px">'+trText('No blocked domains recorded')+'</div>';return;}
    list.innerHTML=d.map(x=>{
      const dom=escapeHtml(x.domain||'');
      const btn=x.blacklisted?'<span class="dns-state err">'+trText('Already in blacklist')+'</span>':
        x.whitelisted?'<span class="dns-state ok">'+trText('Already whitelisted')+'</span>':
        x.canWhitelist===false?'<span class="dns-state dim">'+trText('Not allowed')+'</span>':
        '<button class="sniff-btn modal-btn-primary" style="padding:4px 10px;font-size:11px" data-gw-domain="'+dom+'" onclick="addGatewayWhitelist(this.dataset.gwDomain)">'+trText('Add to Whitelist')+'</button>';
      return '<div class="dns-row">'+
        '<div class="dns-domain" title="'+dom+'">'+dom+'<span class="dns-count">x'+(x.count||0)+'</span></div><div>'+btn+'</div></div>';
    }).join('');
  }catch(e){
    list.innerHTML='<div style="color:var(--tx3);text-align:center;padding:20px">'+trText('DNS filter list unavailable')+': '+(e&&e.message?e.message:'fetch error')+'</div>';
  }
}
async function testGatewayDns(){
  const el=$('gw-test-result'),input=$('gw-test-domain');
  const domain=(input&&input.value?input.value:'').trim();
  if(!domain){if(el){el.textContent=trText('empty domain');el.style.color='var(--err)';}return;}
  try{
    const r=await fetch('/gateway_dns_test?domain='+encodeURIComponent(domain));
    if(!r.ok)throw new Error('HTTP '+r.status);
    const d=await r.json();
    const verdict=d.blocked?trText('would be blocked'):trText('would be allowed');
    const mode=d.mode===0?trText('Blacklist'):trText('Whitelist');
    const reason=trText(d.reason||'');
    const gwState=d.enabled?'':' ('+trText('gateway disabled')+')';
    if(el){
      el.textContent=(d.domain||domain)+' - '+verdict+' - '+mode+' - '+reason+gwState;
      el.style.color=d.blocked?'var(--err)':'var(--ok)';
    }
  }catch(e){
    if(el){el.textContent=trText('DNS test failed')+': '+(e&&e.message?e.message:'network');el.style.color='var(--err)';}
  }
}
async function addGatewayWhitelist(domain){
  const msg=$('gw-blocked-msg')||$('gw-msg');
  try{
    const r=await fetch('/gateway_whitelist_add',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'domain='+encodeURIComponent(domain)});
    const d=await r.json();
    if(!r.ok||!d.ok)throw new Error(d.error||'cannot add domain');
    if(msg){msg.textContent=d.already?trText('Already whitelisted'):trText('Saved')+': '+domain;msg.style.color='var(--ok)';}
    await loadGatewayDns();
    await loadGatewayBlocked();
  }catch(e){if(msg){msg.textContent=trText(e.message||'cannot add domain');msg.style.color='var(--err)';}}
}
async function clearGatewayBlocked(){
  try{
    await fetch('/gateway_blocked_clear',{method:'POST'});
    const list=$('gw-blocked-list');if(list)list.innerHTML='<div style="color:var(--tx3);text-align:center;padding:20px">'+trText('Cleared')+'</div>';
    const sum=$('gw-blocked-summary');if(sum)sum.textContent='';
    loadGatewayStatus();
  }catch(e){}
}
async function loadGatewayBlockedIps(){
  try{
    const r=await fetch('/gateway_blocked_ips');if(!r.ok)throw new Error('unavailable');
    const d=await r.json();
    const el=$('gw-blocked-ips');if(!el)return;
    if(!d.length){el.innerHTML='<div style="color:var(--tx3)">'+trText('No blocked IPs recorded')+'</div>';return;}
    el.innerHTML=d.map(x=>'<div style="display:flex;justify-content:space-between;padding:4px 0;border-bottom:1px solid var(--bd)"><span style="color:var(--tx2);font-family:monospace">'+escapeHtml(x.ip||'')+'</span><span style="color:var(--tx3)">x'+(x.count||0)+'</span></div>').join('');
  }catch(e){
    const el=$('gw-blocked-ips');
    if(el)el.innerHTML='<div style="color:var(--tx3)">'+trText('Blocked IP list unavailable')+'</div>';
  }
}
async function clearGatewayBlockedIps(){
  try{
    await fetch('/gateway_blocked_ips_clear',{method:'POST'});
    const el=$('gw-blocked-ips');if(el)el.textContent='Cleared';
    loadGatewayStatus();
  }catch(e){}
}
// ── Plugin management ──
async function installPlugin(){
  const url=$('plg-url').value;
  if(!url){$('plg-status').textContent='Enter URL';return;}
  const beforeSig=pluginStateSignature(installedPlugins);
  $('plg-status').textContent='Downloading...';$('plg-status').style.color='var(--acc)';
  try{
    await fetchJsonWithTimeout('/plugin_install',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'url='+encodeURIComponent(url)},20000);
    $('plg-url').value='';
    try{await refreshPluginsNow();}catch(e){await refreshPluginsAfterAction(beforeSig);}
    $('plg-status').textContent='Installed';$('plg-status').style.color='var(--ok)';
  }catch(e){
    if(await refreshPluginsAfterAction(beforeSig)){
      $('plg-url').value='';
      $('plg-status').textContent='Installed';$('plg-status').style.color='var(--ok)';
    }else{$('plg-status').textContent=actionErrorMessage(e,'Connection error');$('plg-status').style.color='var(--err)';}
  }
}
async function uploadPlugin(file){
  if(!file)return;
  const beforeSig=pluginStateSignature(installedPlugins);
  $('plg-status').textContent='Uploading...';$('plg-status').style.color='var(--acc)';
  try{
    const text=await file.text();
    await fetchJsonWithTimeout('/plugin_upload',{method:'POST',headers:{'Content-Type':'application/json'},body:text},5000);
    try{await refreshPluginsNow();}catch(e){await refreshPluginsAfterAction(beforeSig);}
    $('plg-status').textContent='Installed';$('plg-status').style.color='var(--ok)';
  }catch(e){
    if(await refreshPluginsAfterAction(beforeSig)){
      $('plg-status').textContent='Installed';$('plg-status').style.color='var(--ok)';
    }else{$('plg-status').textContent=actionErrorMessage(e,'Error');$('plg-status').style.color='var(--err)';}
  }
}
async function pastePlugin(){
  const text=$('plg-paste').value.trim();
  if(!text){$('plg-status').textContent='Paste JSON first';$('plg-status').style.color='var(--err)';return;}
  try{JSON.parse(text);}catch(e){$('plg-status').textContent='Invalid JSON: '+e.message;$('plg-status').style.color='var(--err)';return;}
  const beforeSig=pluginStateSignature(installedPlugins);
  $('plg-status').textContent='Installing...';$('plg-status').style.color='var(--acc)';
  try{
    await fetchJsonWithTimeout('/plugin_upload',{method:'POST',headers:{'Content-Type':'application/json'},body:text},5000);
    $('plg-paste').value='';
    try{await refreshPluginsNow();}catch(e){await refreshPluginsAfterAction(beforeSig);}
    $('plg-status').textContent='Installed';$('plg-status').style.color='var(--ok)';
  }catch(e){
    if(await refreshPluginsAfterAction(beforeSig)){
      $('plg-paste').value='';
      $('plg-status').textContent='Installed';$('plg-status').style.color='var(--ok)';
    }else{$('plg-status').textContent=actionErrorMessage(e,'Connection error');$('plg-status').style.color='var(--err)';}
  }
}
async function togglePlugin(idx){
  const beforeSig=pluginStateSignature(installedPlugins);
  try{
    const d=await fetchJsonWithTimeout('/plugin_toggle',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'idx='+idx},4000);
    if(installedPlugins[idx]&&typeof d.enabled==='boolean'){
      installedPlugins[idx].enabled=d.enabled;
      renderPluginsState({plugins:installedPlugins,maxPlugins:pluginMax});
    }else{
      try{await refreshPluginsNow();}catch(e){await refreshPluginsAfterAction(beforeSig);}
    }
  }catch(e){await refreshPluginsAfterAction(beforeSig);}
}
async function removePlugin(idx){
  if(!await dashConfirm('Remove this plugin?','Remove plugin','Remove'))return;
  const beforeSig=pluginStateSignature(installedPlugins);
  try{
    await fetchJsonWithTimeout('/plugin_remove',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'idx='+idx},4000);
    try{await refreshPluginsNow();}catch(e){await refreshPluginsAfterAction(beforeSig);}
  }catch(e){await refreshPluginsAfterAction(beforeSig);}
}
async function setPluginPriority(idx,value){
  const to=parseInt(value,10)-1;
  if(isNaN(to)||to===idx){renderPluginsState({plugins:installedPlugins,maxPlugins:pluginMax});return;}
  const beforeSig=pluginStateSignature(installedPlugins);
  try{
    await fetchJsonWithTimeout('/plugin_priority',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'idx='+idx+'&priority='+to},4000);
    try{await refreshPluginsNow();}catch(e){await refreshPluginsAfterAction(beforeSig);}
  }catch(e){await refreshPluginsAfterAction(beforeSig);}
}
function pluginByteBits(byte,mask){
  byte=parseInt(byte,10);mask=(parseInt(mask,10)||0)&255;
  const bits=[];
  if(isNaN(byte)||byte<0||byte>7)return bits;
  for(let b=0;b<8;b++)if(mask&(1<<b))bits.push(byte*8+b);
  return bits;
}
function pluginOpBits(o){
  if(!o)return[];
  if(o.type==='set_bit'){
    const bit=parseInt(o.bit,10);
    return !isNaN(bit)&&bit>=0&&bit<64?[bit]:[];
  }
  if(o.type==='set_byte')return pluginByteBits(o.byte,o.mask===undefined?255:o.mask);
  if(o.type==='or_byte')return pluginByteBits(o.byte,o.val||0);
  if(o.type==='and_byte')return pluginByteBits(o.byte,(~(o.val===undefined?255:o.val))&255);
  if(o.type==='counter')return pluginByteBits(o.byte,o.mask===undefined?15:o.mask);
  if(o.type==='checksum')return pluginByteBits(7,255);
  if(o.type==='emit_periodic')return[];
  return[];
}
function pluginRuleMuxMask(r){return r&&typeof r.mux_mask==='number'?r.mux_mask:peDefaultMuxMask(r&&typeof r.mux==='number'?r.mux:-1);}
function pluginRuleMatchMask(r){return r&&typeof r.match_mask==='number'?r.match_mask:0;}
function pluginMuxesOverlap(a,am,b,bm){if(a<0||b<0)return true;const mask=(am||peDefaultMuxMask(a))&(bm||peDefaultMuxMask(b));return !mask||((a&mask)===(b&mask));}
function pluginBusesOverlap(a,b){return !a||!b||((a&b)!==0);}
function pluginByteMatchesOverlap(a,b){
  const am=pluginRuleMatchMask(a),bm=pluginRuleMatchMask(b);
  if(!am||!bm)return true;
  if(a.match_byte!==b.match_byte)return true;
  const mask=am&bm;
  return !mask||(((a.match_val||0)&mask)===((b.match_val||0)&mask));
}
function pluginFormatBits(bits){
  bits=Array.from(new Set(bits)).sort((a,b)=>a-b);
  if(bits.length>6)return bits.slice(0,6).join(', ')+', +'+(bits.length-6)+' more';
  return bits.join(', ');
}
function pluginConflictGroups(conflicts){
  const grouped={};
  (conflicts||[]).forEach(c=>{
    const key=c.winner+'|'+c.winnerPriority;
    if(!grouped[key])grouped[key]={winner:c.winner,winnerPriority:c.winnerPriority,bits:[]};
    grouped[key].bits.push(c.bit);
  });
  return Object.keys(grouped).map(k=>grouped[k]);
}
function pluginAnalyzePriority(list){
  const owners=[];
  (list||[]).forEach((p,i)=>{
    p.priority=i+1;p.hasConflict=false;
    (p.details||[]).forEach(r=>{r.pluginConflict=false;r.conflicts=[];});
  });
  (list||[]).forEach((p,i)=>{
    if(!p.enabled)return;
    (p.details||[]).forEach(r=>{
      if(r.send===false)return;
      const conflicts=[];
      (r.ops||[]).forEach(o=>{
        pluginOpBits(o).forEach(bit=>{
          const owner=owners.find(x=>x.id===r.id&&pluginBusesOverlap(x.bus,r.bus)&&pluginMuxesOverlap(x.mux,x.mux_mask,r.mux,pluginRuleMuxMask(r))&&pluginByteMatchesOverlap(x,r)&&x.bit===bit);
          if(owner){
            if(owner.plugin!==p.name)conflicts.push({bit:bit,winner:owner.plugin,winnerPriority:owner.priority});
          }else owners.push({id:r.id,bus:r.bus||0,mux:r.mux,mux_mask:pluginRuleMuxMask(r),match_byte:r.match_byte,match_mask:r.match_mask,match_val:r.match_val,bit:bit,plugin:p.name,priority:i+1});
        });
      });
      if(conflicts.length){r.pluginConflict=true;r.conflicts=conflicts;p.hasConflict=true;}
    });
  });
}
function renderPluginConflictPanel(list){
  const el=$('plg-conflicts');
  if(!el)return;
  if(!list.length){el.style.display='none';el.innerHTML='';return;}
  const first=(list||[]).find(p=>p.enabled);
  const rows=[];
  (list||[]).forEach(p=>(p.details||[]).forEach(r=>{
    if(r.pluginConflict)pluginConflictGroups(r.conflicts).forEach(g=>{
      rows.push('<div>CAN '+r.hex+(r.bus?(' '+peBusLabel(r.bus)):'')+(r.mux>=0?' mux '+r.mux+'/0x'+pluginRuleMuxMask(r).toString(16):' any mux')+': '+p.name+' ignores bit '+pluginFormatBits(g.bits)+'; '+g.winner+' (#'+g.winnerPriority+') wins</div>');
    });
  }));
  let h='<div style="padding:8px;background:var(--bg2);border:1px solid var(--bd);border-radius:6px;font-size:11px;color:var(--tx3);line-height:1.5">';
  h+='<div style="color:var(--tx2);font-weight:600;margin-bottom:3px">Injection priority</div>';
  h+=first?('#'+first.priority+' '+first.name+' is the first enabled plugin; the merged frame is injected after plugin bits are resolved; GTW 2047 uses the configured replay count.'):
    'No enabled plugins are injecting frames.';
  if(rows.length){
    h+='<div style="margin-top:6px;color:var(--warn)">'+rows.slice(0,5).join('')+(rows.length>5?'<div>+'+(rows.length-5)+' more conflicts</div>':'')+'</div>';
  }
  el.innerHTML=h+'</div>';
  el.style.display='block';
}
function pluginPrioritySelect(idx,total){
  if(total<2)return'';
  let h='<select class="sniff-input" title="Set injection priority" onchange="setPluginPriority('+idx+',this.value)" style="flex:0 0 58px;width:58px;margin-left:8px;padding:4px;font-size:10px">';
  for(let i=1;i<=total;i++)h+='<option value="'+i+'" '+(i===idx+1?'selected':'')+'>#'+i+'</option>';
  return h+'</select>';
}
function fmtOp(o){
  if(o.type==='set_bit') return 'set_bit('+o.bit+', '+(o.val?'true':'false')+')';
  if(o.type==='checksum') return 'checksum(byte 7)';
  if(o.type==='counter') return 'counter('+o.byte+', mask=0x'+((o.mask===undefined?15:o.mask)&255).toString(16)+', step='+(o.step||1)+')';
  if(o.type==='emit_periodic') return 'emit_periodic('+((o.interval||100)|0)+' ms'+(o.gtw_silent?', GTW silent':'')+')';
  if(o.type==='set_byte') return 'set_byte('+o.byte+', 0x'+o.val.toString(16)+', mask=0x'+o.mask.toString(16)+')';
  if(o.type==='or_byte') return 'or_byte('+o.byte+', 0x'+o.val.toString(16)+')';
  if(o.type==='and_byte') return 'and_byte('+o.byte+', 0x'+o.val.toString(16)+')';
  return o.type;
}
function fmtRuleMatch(r){
  const mask=pluginRuleMatchMask(r);
  if(!mask)return '';
  return 'byte['+(r.match_byte||0)+']&0x'+(mask&255).toString(16)+'=0x'+((r.match_val||0)&255).toString(16);
}
function renderPluginDetails(details){
  return '<div style="margin-top:6px;padding:8px;background:var(--bg2);border-radius:6px;font-size:11px;font-family:monospace">'
    +details.map(r=>{
      let hdr='<div style="margin-bottom:4px"><b>CAN '+r.hex+' ('+r.id+')</b>';
      if(r.bus) hdr+=' <span style="color:var(--acc)">'+peBusLabel(r.bus)+'</span>';
      if(r.mux>=0) hdr+=' <span style="color:var(--acc)">mux='+r.mux+'/0x'+pluginRuleMuxMask(r).toString(16)+'</span>';
      if(pluginRuleMatchMask(r)) hdr+=' <span style="color:var(--acc)">'+fmtRuleMatch(r)+'</span>';
      if(r.pluginConflict) hdr+=' <span style="color:var(--warn);font-weight:bold" title="Lower priority bits are ignored">&#9888; Priority overlap</span>';
      hdr+='</div>';
      let ops=r.ops.map(o=>'<div style="padding-left:12px;color:var(--tx2)">'+fmtOp(o)+'</div>').join('');
      let notes='';
      if(r.pluginConflict){
        notes='<div style="margin-top:4px;padding-left:12px;color:var(--warn)">'+pluginConflictGroups(r.conflicts).map(g=>'bit '+pluginFormatBits(g.bits)+' ignored; '+g.winner+' (#'+g.winnerPriority+') wins').join('<br>')+'</div>';
      }
      return hdr+ops+notes;
    }).join('<div style="border-top:1px solid var(--bd);margin:4px 0"></div>')
    +'</div>';
}
function toggleDetails(idx){
  var p=installedPlugins[idx];
  if(!p||!p.name)return;
  pluginDetailOpen[p.name]=!pluginDetailOpen[p.name];
  var el=$('plg-det-'+idx);
  if(el)el.style.display=pluginDetailOpen[p.name]?'block':'none';
}
function toggleInfo(id){
  var el=$(id);
  if(el)el.style.display=el.style.display==='none'?'block':'none';
}

function openHelpParent(btn){
  var sec=btn.closest('.subsec');
  if(sec&&sec.classList.contains('collapsed')){
    sec.classList.remove('collapsed');
    if(sec.dataset.collapseKey)localStorage.setItem(sec.dataset.collapseKey,'0');
    var secBtn=sec.querySelector('.subsec-btn');
    if(secBtn)secBtn.textContent='Hide';
  }
  var card=btn.closest('.card');
  if(card&&card.classList.contains('collapsed')){
    card.classList.remove('collapsed');
    if(card.dataset.collapseKey)localStorage.setItem(card.dataset.collapseKey,'0');
    var cardBtn=card.querySelector('.card-min-btn');
    if(cardBtn)cardBtn.textContent='Hide';
  }
}

function closeHelpPanels(scope,exceptId){
  (scope||document).querySelectorAll('.inline-help-panel').forEach(function(panel){
    if(!exceptId||panel.id!==exceptId)panel.classList.remove('show');
  });
}

function toggleHelp(btn,ev){
  if(ev){
    ev.preventDefault();
    ev.stopPropagation();
  }

  openHelpParent(btn);

  var targetId=btn.getAttribute('data-help-target');
  var panelId=btn.getAttribute('data-inline-help-id');
  var panel=panelId?document.getElementById(panelId):null;

  if(!panel){
    panel=document.createElement('div');
    panel.className='inline-help-panel';
    panelId='inline-help-'+Math.random().toString(36).slice(2,10);
    panel.id=panelId;
    btn.setAttribute('data-inline-help-id',panelId);

    var anchor=btn.closest('.subsec-head, .card-hdr, .setting-name, summary');
    if(anchor&&anchor.parentNode){
      anchor.insertAdjacentElement('afterend',panel);
    }else if(btn.parentNode){
      btn.parentNode.insertAdjacentElement('afterend',panel);
    }
  }

  if(targetId){
    var target=document.getElementById(targetId);
    panel.innerHTML=target?target.innerHTML:'More information is not available yet.';
  }else{
    panel.textContent=btn.getAttribute('data-help')||btn.getAttribute('title')||'More information is not available yet.';
  }

  var scope=btn.closest('.subsec, .card')||document;
  var willShow=!panel.classList.contains('show');
  closeHelpPanels(scope,panelId);
  panel.classList.toggle('show',willShow);
  return false;
}

function pluginStateSignature(list){
  return JSON.stringify((list||[]).map(p=>[p&&p.name||'',p&&p.version||'',!!(p&&p.enabled),p&&p.rules||0,p&&p.author||'']));
}

const GTW_UDS_STATE_NAMES=['Idle','Session req','Seed req','Key sent','CommCtrl sent','Active','Failed'];
function renderGtwUdsStatus(d){
  const el=$('plg-gtw-status');if(!el)return;
  const supported=!!d.gtw_silent_supported;
  const uds=d.gtw_uds||{};
  const active=pluginHasAnyGtwSilent(d.plugins||[]);
  if(!active&&!supported){el.style.display='none';return;}
  el.style.display='block';
  const stateIdx=typeof uds.state==='number'?uds.state:0;
  const stateName=GTW_UDS_STATE_NAMES[stateIdx]||('State '+stateIdx);
  const stateColor=stateIdx===5?'var(--ok)':stateIdx===6?'var(--err)':'var(--tx3)';
  let h='<div style="padding:8px 10px;background:var(--bg2);border:1px solid var(--bd);border-radius:6px;font-size:11px">';
  h+='<div style="display:flex;align-items:center;gap:8px;flex-wrap:wrap">';
  if(supported){
    h+='<span style="color:var(--ok);font-weight:bold">&#10003; GTW silent: custom key loaded</span>';
  }else{
    h+='<span style="color:var(--tx3)">&#10007; GTW silent: no key &mdash; <code>PLUGIN_GTW_UDS_CUSTOM_KEY</code> not defined, <code>gtw_silent</code> disabled</span>';
  }
  if(active&&supported){
    h+='<span style="color:'+stateColor+';margin-left:auto">UDS: '+stateName+'</span>';
    if(uds.last_seed&&uds.last_seed.length>0){
      h+='</div><div style="margin-top:6px;font-family:monospace;color:var(--tx2)">';
      h+='seed&nbsp;&rarr;&nbsp;<b>'+uds.last_seed+'</b>&nbsp;&nbsp;key&nbsp;&rarr;&nbsp;<b style="color:var(--ok)">'+uds.last_key+'</b>';
      if(uds.last_nrc&&uds.last_nrc!==0)h+='&nbsp;&nbsp;<span style="color:var(--err)">NRC 0x'+uds.last_nrc.toString(16)+'</span>';
    }
  }
  h+='</div></div>';
  el.innerHTML=h;
}
function pluginHasAnyGtwSilent(plugins){
  return (plugins||[]).some(p=>(p.details||[]).some(r=>(r.ops||[]).some(o=>o.type==='emit_periodic'&&o.gtw_silent)));
}
function renderPluginsState(d){
  installedPlugins=d.plugins||[];
  pluginAnalyzePriority(installedPlugins);
  const nextOpen={};
  installedPlugins.forEach(p=>{if(p&&p.name&&pluginDetailOpen[p.name])nextOpen[p.name]=true;});
  pluginDetailOpen=nextOpen;
  pluginMax=d.maxPlugins||pluginMax||0;
  renderGtwUdsStatus(d);
  const max=pluginMax;
  $('plg-count').textContent=max?installedPlugins.length+' / '+max+' installed':installedPlugins.length+' installed';
  if($('plg-limit')){
    const full=max&&installedPlugins.length>=max;
    $('plg-limit').textContent=max?(full?'Maximum '+max+' plugins reached. Remove one before installing another.':'Maximum '+max+' plugins total. Remove one before installing another.'):'Maximum plugins: --';
    $('plg-limit').style.color=full?'var(--err)':'var(--tx3)';
  }
  const el=$('plg-list');
  if(!installedPlugins.length){
    renderPluginConflictPanel(installedPlugins);
    el.innerHTML='<div style="font-size:12px;color:var(--tx3);text-align:center;padding:12px">No plugins installed</div>';
    return;
  }
  renderPluginConflictPanel(installedPlugins);
  el.innerHTML=installedPlugins.map((p,i)=>{
    let detailsOpen=!!pluginDetailOpen[p.name];
    let row='<div style="margin-bottom:8px;padding-bottom:8px;border-bottom:1px solid var(--bd)">';
    row+='<div class="setting-row"><div class="setting-info" style="cursor:pointer" onclick="toggleDetails('+i+')">';
    row+='<div class="setting-name">'+p.name+' <span style="color:var(--tx3);font-size:11px">v'+p.version+'</span>';
    row+='</div>';
    row+='<div class="setting-desc">Priority #'+(i+1)+(i===0?' first':'')+' &bull; '+p.rules+' rule'+(p.rules!==1?'s':'')+(p.author?' &bull; '+p.author:'')+(p.hasConflict?' &bull; <span style="color:var(--warn)">overlap ignored</span>':'')+' &bull; <span style="color:var(--acc);cursor:pointer">details</span></div>';
    row+='</div>';
    row+=pluginPrioritySelect(i,installedPlugins.length);
    row+='<label class="tgl"><input type="checkbox" '+(p.enabled?'checked':'')+' onchange="togglePlugin('+i+')"><div class="tgl-track"><div class="tgl-thumb"></div></div></label>';
    row+='<button onclick="peLoadInstalledPlugin('+i+')" style="margin-left:8px;padding:4px 8px;border:1px solid var(--bd);border-radius:5px;background:transparent;color:var(--acc);cursor:pointer;font-size:10px;font-family:inherit">Edit</button>';
    row+='<button onclick="removePlugin('+i+')" style="margin-left:8px;padding:4px 8px;border:1px solid var(--errBd);border-radius:5px;background:transparent;color:var(--err);cursor:pointer;font-size:10px;font-family:inherit">X</button></div>';
    if(p.details){
      row+='<div id="plg-det-'+i+'" style="display:'+(detailsOpen?'block':'none')+'">';
      row+=renderPluginDetails(p.details);
      row+='</div>';
    }
    row+='</div>';
    return row;
  }).join('');
}

async function refreshPluginsNow(){
  const d=await fetchJsonWithTimeout('/plugins',null,2500);
  renderPluginsState(d);
  return d;
}

async function refreshPluginsAfterAction(beforeSig){
  for(let i=0;i<4;i++){
    if(i)await waitMs(250);
    try{
      await refreshPluginsNow();
      if(pluginStateSignature(installedPlugins)!==beforeSig)return true;
    }catch(e){}
  }
  return false;
}

async function pollPlugins(){
  return runPoll('plugins',async()=>{
    if(!dashboardStatusOk)return;
    try{renderPluginsState(await fetchPollJson('/plugins',2000));}catch(e){}
  });
}

// ── Firmware update ──
var pendingUpdateUrl='';
async function toggleBeta(){
  const beta=$('beta-tgl').checked?'1':'0';
  try{await fetch('/update_beta',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'beta='+beta});}catch(e){}
  $('upd-info').style.display='none';$('upd-status').textContent='';
}
async function checkUpdate(){
  $('upd-check-btn').disabled=true;$('upd-status').textContent='Checking...';$('upd-status').style.color='var(--acc)';
  $('upd-info').style.display='none';pendingUpdateUrl='';
  try{const r=await fetch('/update_check');const d=await r.json();
    if(!d.ok){$('upd-status').textContent=d.error||'Error';$('upd-status').style.color='var(--err)';const m=$('manual-fw-upload');if(m)m.open=true;$('upd-check-btn').disabled=false;return;}
    $('fw-ver').textContent='v'+d.current;
    if(d.update){
      $('upd-status').textContent='Update available!';$('upd-status').style.color='var(--ok)';
      $('upd-ver').textContent='v'+d.latest+(d.prerelease?' (beta)':'');
      $('upd-detail').textContent=d.artifact+' \u2022 '+d.tag;
      pendingUpdateUrl=d.url;
      $('upd-info').style.display='block';
    }else{
      $('upd-status').textContent='Up to date (v'+d.current+')';$('upd-status').style.color='var(--ok)';
    }
  }catch(e){$('upd-status').textContent='Connection error';$('upd-status').style.color='var(--err)';}
  $('upd-check-btn').disabled=false;
}
async function installUpdate(){
  if(!pendingUpdateUrl){$('upd-status').textContent='No update URL';return;}
  if(!await dashConfirm('Install firmware update? The device will reboot.','Install update','Install'))return;
  $('upd-install-btn').disabled=true;$('upd-status').textContent='Downloading & installing...';$('upd-status').style.color='var(--acc)';
  try{await fetch('/update_install',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'url='+encodeURIComponent(pendingUpdateUrl)});
    $('upd-status').textContent='Update installed! Rebooting...';$('upd-status').style.color='var(--ok)';
    setTimeout(()=>location.reload(),15000);
  }catch(e){$('upd-status').textContent='Update failed';$('upd-status').style.color='var(--err)';$('upd-install-btn').disabled=false;}
}
async function loadUpdateInfo(){
  try{const r=await fetch('/update_beta',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'noop=1'});
    const d=await r.json();
    if(d.version){$('fw-ver').textContent='v'+d.version;updateFoot(d.version);}
    $('beta-tgl').checked=!!d.beta;
  }catch(e){}
  try{const r=await fetch('/auto_update');const d=await r.json();$('auto-upd-tgl').checked=!!d.enabled;}catch(e){}
}
async function toggleAutoUpdate(){
  const en=$('auto-upd-tgl').checked?'1':'0';
  try{await fetch('/auto_update',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'enabled='+en});}catch(e){}
}
function updateFoot(ver){
  var ip=location.hostname||'100.100.1.1';
  $('dash-foot').textContent='ev-open-can-tools \u2022 v'+ver+' \u2022 '+ip;
}

async function loadCanPins(){
  try{const r=await fetch('/can_pins');const d=await r.json();
    if(d.tx>=0)$('can-tx').value=d.tx;
    if(d.rx>=0)$('can-rx').value=d.rx;
    $('can-pins-status').textContent=d.customized?('custom TX='+d.tx+' RX='+d.rx):('firmware default TX='+d.tx+' RX='+d.rx);
  }catch(e){}
}
async function saveCanPins(){
  var tx=parseInt($('can-tx').value,10),rx=parseInt($('can-rx').value,10);
  if(isNaN(tx)||isNaN(rx)){$('can-pins-hint').textContent='Enter both TX and RX';$('can-pins-hint').style.color='var(--err)';return;}
  if(!await dashConfirm('Save CAN pins TX='+tx+' RX='+rx+' and reboot? Wrong pins disable CAN.','Save CAN pins','Save'))return;
  try{const r=await fetch('/can_pins',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'tx='+tx+'&rx='+rx});
    const d=await r.json();
    if(d.ok){
      $('can-pins-hint').textContent='Saved. Rebooting...';$('can-pins-hint').style.color='var(--ok)';
      await fetch('/reboot',{method:'POST'});
      setTimeout(()=>location.reload(),8000);
    }else{
      $('can-pins-hint').textContent=d.error||'Save failed';$('can-pins-hint').style.color='var(--err)';
    }
  }catch(e){$('can-pins-hint').textContent='Connection error';$('can-pins-hint').style.color='var(--err)';}
}

async function exportSettings(){
  $('backup-status').textContent='Preparing...';$('backup-status').style.color='var(--tx3)';
  try{const r=await fetch('/settings_export');
    if(!r.ok){throw new Error('HTTP '+r.status);}
    const text=await r.text();
    const blob=new Blob([text],{type:'application/json'});
    const url=URL.createObjectURL(blob);
    const a=document.createElement('a');a.href=url;a.download='evtools-backup.json';document.body.appendChild(a);a.click();document.body.removeChild(a);URL.revokeObjectURL(url);
    $('backup-status').textContent='Downloaded';$('backup-status').style.color='var(--ok)';
  }catch(e){$('backup-status').textContent='Export failed';$('backup-status').style.color='var(--err)';}
}
async function importSettings(ev){
  const f=ev.target.files[0];if(!f)return;
  const text=await f.text();
  try{JSON.parse(text);}catch(e){$('backup-status').textContent='Invalid JSON';$('backup-status').style.color='var(--err)';return;}
  if(!await dashConfirm('Restore settings from '+f.name+' and reboot?','Restore settings','Restore'))return;
  $('backup-status').textContent='Uploading...';$('backup-status').style.color='var(--acc)';
  try{const r=await fetch('/settings_import',{method:'POST',headers:{'Content-Type':'application/json'},body:text});
    const d=await r.json();
    if(d.ok){
      $('backup-status').textContent='Restored. Rebooting...';$('backup-status').style.color='var(--ok)';
      await fetch('/reboot',{method:'POST'});
      setTimeout(()=>location.reload(),8000);
    }else{
      $('backup-status').textContent=d.error||'Import failed';$('backup-status').style.color='var(--err)';
    }
  }catch(e){$('backup-status').textContent='Upload failed';$('backup-status').style.color='var(--err)';}
  ev.target.value='';
}

// ── Plugin Editor ────────────────────────────────────────────────
let peState={rules:[]};
function peGetMeta(){return{name:($('pe-name').value||'').trim(),version:($('pe-version').value||'1.0').trim(),author:($('pe-author').value||'').trim()};}
function peParseInt(s,def){if(typeof s==='number')return s;if(s===''||s==null)return def;s=String(s).trim();let n=s.toLowerCase().startsWith('0x')?parseInt(s,16):parseInt(s,10);return isNaN(n)?def:n;}
function peBusLabel(v){if(v===undefined||v===null||v===''||v===0)return'';if(Array.isArray(v))return v.join(',');if(typeof v==='number'){let out=[];if(v&1)out.push('CH');if(v&2)out.push('VEH');if(v&4)out.push('PARTY');return out.join(',');}return String(v);}
function peDefaultMuxMask(mux){return mux<0?0:(mux>7?255:7);}
function peSetStatus(msg,kind){const el=$('pe-status');el.textContent=msg;el.style.color=kind==='ok'?'var(--ok)':kind==='err'?'var(--err)':kind==='acc'?'var(--acc)':'var(--tx3)';}
function peSetTestStatus(msg,kind){const el=$('pe-test-status');el.textContent=msg;el.style.color=kind==='ok'?'var(--ok)':kind==='err'?'var(--err)':kind==='acc'?'var(--acc)':'var(--tx3)';}
function peHasContent(){const meta=peGetMeta();return !!(meta.name||meta.author||meta.version!=='1.0'||peState.rules.length);}
function peRuleLabel(r,i){return 'Rule '+(i+1)+' · CAN 0x'+toHex((r.id||0)&0x7FF,3)+(r.mux>=0?' · mux '+r.mux:'')+(peBusLabel(r.bus)?' · '+peBusLabel(r.bus):'')+(pluginRuleMatchMask(r)?' · '+fmtRuleMatch(r):'');}
function peParseShortcutLine(line){
  const raw=(line||'').trim();
  if(!raw)return{error:'Shortcut line required'};
  const m=raw.match(/^\s*(0x[0-9a-fA-F]+|\d+)(?:\s+mux\s*=\s*(-?\d+))?\s+byte\[(\d+)\]\s*=\s*(0x[0-9a-fA-F]+|\d+)(?:\s+mask\s*=\s*(0x[0-9a-fA-F]+|\d+))?(?:\s*\((.*)\))?\s*$/);
  if(!m)return{error:'Use format like 0x7FF mux=2 byte[5] = 0x4C'};
  const canId=peParseInt(m[1],NaN),mux=m[2]===undefined?-1:peParseInt(m[2],NaN);
  const byte=peParseInt(m[3],NaN),val=peParseInt(m[4],NaN),mask=m[5]===undefined?255:peParseInt(m[5],NaN);
  if(isNaN(canId)||canId<1||canId>0x7FF)return{error:'CAN ID must be 1-0x7FF'};
  if(isNaN(mux)||mux<-1||mux>255)return{error:'mux must be -1..255'};
  if(isNaN(byte)||byte<0||byte>7)return{error:'byte must be 0-7'};
  if(isNaN(val)||val<0||val>255)return{error:'value must be 0-255'};
  if(isNaN(mask)||mask<0||mask>255)return{error:'mask must be 0-255'};
  return{rule:{id:canId|0,mux:mux|0,mux_mask:peDefaultMuxMask(mux|0),bus:'',send:true,ops:[{type:'set_byte',byte:byte|0,val:val|0,mask:mask|0}]},note:raw};
}
function peUpdateRuleOptions(){
  const sel=$('pe-test-rule');if(!sel)return;
  const prev=parseInt(sel.value,10);
  if(!peState.rules.length){sel.disabled=true;sel.innerHTML='<option value="">No rules</option>';return;}
  sel.disabled=false;
  sel.innerHTML=peState.rules.map((r,i)=>'<option value="'+i+'">'+peRuleLabel(r,i)+'</option>').join('');
  sel.value=String(!isNaN(prev)&&prev>=0&&prev<peState.rules.length?prev:0);
}
function peAddRule(){if(peState.rules.length>=16){peSetStatus('Max 16 rules per plugin','err');return;}peState.rules.push({id:0,mux:-1,mux_mask:0,bus:'',match_byte:0,match_mask:0,match_val:0,send:true,ops:[]});peRender();}
function peAddRuleFromShortcut(){
  if(peState.rules.length>=16){peSetStatus('Max 16 rules per plugin','err');return;}
  const input=$('pe-shortcut');const parsed=peParseShortcutLine(input.value);
  if(parsed.error){peSetStatus(parsed.error,'err');return;}
  peState.rules.push(parsed.rule);
  input.value='';
  peRender();
  peSetStatus('Shortcut added','ok');
}
function peRemoveRule(i){peState.rules.splice(i,1);peRender();}
function peAddOp(i,type){const r=peState.rules[i];if(!r)return;if(r.ops.length>=peMaxOps){peSetStatus('Max '+peMaxOps+' ops per rule','err');return;}
  const op={type:type};
  if(type==='set_bit'){op.bit=0;op.val=1;}
  else if(type==='set_byte'){op.byte=0;op.val=0;op.mask=255;}
  else if(type==='or_byte'){op.byte=0;op.val=0;}
  else if(type==='and_byte'){op.byte=0;op.val=255;}
  else if(type==='counter'){op.byte=0;op.mask=15;op.step=1;}
  else if(type==='emit_periodic'){op.interval=100;op.gtw_silent=false;}
  r.ops.push(op);peRender();}
function peRemoveOp(i,j){peState.rules[i].ops.splice(j,1);peRender();}
function peUpdateField(i,j,field,value){
  if(j<0){const r=peState.rules[i];if(!r)return;
    if(field==='id')r.id=peParseInt(value,0);
    else if(field==='mux'){const oldDefault=peDefaultMuxMask(r.mux);const oldMask=r.mux_mask||0;r.mux=value===''?-1:peParseInt(value,-1);if(!oldMask||oldMask===oldDefault)r.mux_mask=peDefaultMuxMask(r.mux);}
    else if(field==='mux_mask')r.mux_mask=Math.max(0,Math.min(255,peParseInt(value,peDefaultMuxMask(r.mux))));
    else if(field==='bus')r.bus=String(value||'').trim().toUpperCase();
    else if(field==='match_byte')r.match_byte=Math.max(0,Math.min(7,peParseInt(value,0)));
    else if(field==='match_mask')r.match_mask=Math.max(0,Math.min(255,peParseInt(value,0)));
    else if(field==='match_val')r.match_val=Math.max(0,Math.min(255,peParseInt(value,0)));
    else if(field==='send')r.send=!!value;
    peRender();return;
  }
  const op=peState.rules[i].ops[j];if(!op)return;
  if(field==='type'){const nt=value;Object.keys(op).forEach(k=>{if(k!=='type')delete op[k];});op.type=nt;
    if(nt==='set_bit'){op.bit=0;op.val=1;}
    else if(nt==='set_byte'){op.byte=0;op.val=0;op.mask=255;}
    else if(nt==='or_byte'){op.byte=0;op.val=0;}
    else if(nt==='and_byte'){op.byte=0;op.val=255;}
    else if(nt==='counter'){op.byte=0;op.mask=15;op.step=1;}
    else if(nt==='emit_periodic'){op.interval=100;op.gtw_silent=false;}
    peRender();return;
  }
  if(field==='bit')op.bit=Math.max(0,Math.min(63,peParseInt(value,0)));
  else if(field==='byte')op.byte=Math.max(0,Math.min(7,peParseInt(value,0)));
  else if(field==='val')op.val=Math.max(0,Math.min(op.type==='set_bit'?1:255,peParseInt(value,0)));
  else if(field==='mask')op.mask=Math.max(0,Math.min(255,peParseInt(value,255)));
  else if(field==='step')op.step=Math.max(1,Math.min(255,peParseInt(value,1)));
  else if(field==='interval')op.interval=Math.max(10,Math.min(5000,peParseInt(value,100)));
  else if(field==='gtw_silent')op.gtw_silent=!!value;
  peRenderPreview();peUpdateTestPreview();
}
function peOpRow(i,j,op){
  const sel='<select class="sniff-input" style="width:90px" onchange="peUpdateField('+i+','+j+',\'type\',this.value)">'+
    ['set_bit','set_byte','or_byte','and_byte','counter','emit_periodic','checksum'].map(t=>'<option value="'+t+'"'+(op.type===t?' selected':'')+'>'+t+'</option>').join('')+'</select>';
  let fields='';
  if(op.type==='set_bit'){
    fields='<input class="sniff-input" style="width:55px" type="number" min="0" max="63" value="'+op.bit+'" title="bit (0-63)" onchange="peUpdateField('+i+','+j+',\'bit\',this.value)">'+
      '<select class="sniff-input" style="width:80px" onchange="peUpdateField('+i+','+j+',\'val\',this.value)"><option value="1"'+(op.val?' selected':'')+'>set (1)</option><option value="0"'+(!op.val?' selected':'')+'>clear (0)</option></select>';
  }else if(op.type==='set_byte'){
    fields='<input class="sniff-input" style="width:48px" type="number" min="0" max="7" value="'+op.byte+'" title="byte (0-7)" onchange="peUpdateField('+i+','+j+',\'byte\',this.value)">'+
      '<input class="sniff-input" style="width:70px" value="0x'+((op.val||0)&255).toString(16)+'" title="val (0-255, hex or dec)" onchange="peUpdateField('+i+','+j+',\'val\',this.value)">'+
      '<input class="sniff-input" style="width:70px" value="0x'+(op.mask===undefined?255:op.mask).toString(16)+'" title="mask (0-255)" onchange="peUpdateField('+i+','+j+',\'mask\',this.value)">';
  }else if(op.type==='or_byte'||op.type==='and_byte'){
    fields='<input class="sniff-input" style="width:48px" type="number" min="0" max="7" value="'+op.byte+'" title="byte (0-7)" onchange="peUpdateField('+i+','+j+',\'byte\',this.value)">'+
      '<input class="sniff-input" style="width:70px" value="0x'+((op.val||0)&255).toString(16)+'" title="val (0-255)" onchange="peUpdateField('+i+','+j+',\'val\',this.value)">';
  }else if(op.type==='counter'){
    fields='<input class="sniff-input" style="width:48px" type="number" min="0" max="7" value="'+op.byte+'" title="byte (0-7)" onchange="peUpdateField('+i+','+j+',\'byte\',this.value)">'+
      '<input class="sniff-input" style="width:70px" value="0x'+((op.mask===undefined?15:op.mask)&255).toString(16)+'" title="counter mask (contiguous bits)" onchange="peUpdateField('+i+','+j+',\'mask\',this.value)">'+
      '<input class="sniff-input" style="width:58px" type="number" min="1" max="255" value="'+(op.step||1)+'" title="step" onchange="peUpdateField('+i+','+j+',\'step\',this.value)">';
  }else if(op.type==='emit_periodic'){
    fields='<input class="sniff-input" style="width:72px" type="number" min="10" max="5000" value="'+(op.interval||100)+'" title="interval ms" onchange="peUpdateField('+i+','+j+',\'interval\',this.value)">'+
      '<label style="font-size:11px;color:var(--tx3);display:flex;align-items:center;gap:4px"><input type="checkbox"'+(op.gtw_silent?' checked':'')+' onchange="peUpdateField('+i+','+j+',\'gtw_silent\',this.checked)"> GTW silent</label>';
  }else{
    fields='<span style="font-size:11px;color:var(--tx3);align-self:center;padding:0 4px">recalc byte 7 checksum</span>';
  }
  return '<div style="display:flex;gap:4px;align-items:center;margin-bottom:4px;flex-wrap:wrap">'+sel+fields+'<button class="sniff-btn" style="margin-left:auto;padding:2px 8px" onclick="peRemoveOp('+i+','+j+')" title="Remove op">&times;</button></div>';
}
function peRuleBlock(i,r){
  const ops=r.ops.length?r.ops.map((op,j)=>peOpRow(i,j,op)).join(''):'<div style="font-size:11px;color:var(--tx3);padding:4px 0">No ops &mdash; add one below</div>';
  const hex=r.id?'0x'+r.id.toString(16).toUpperCase():'?';
  const muxMask=r.mux_mask===undefined?peDefaultMuxMask(r.mux):r.mux_mask;
  return '<details open style="margin-bottom:10px;border:1px solid var(--bd);border-radius:6px;padding:8px;background:var(--bg2)">'+
    '<summary style="cursor:pointer;font-size:12px;color:var(--tx);user-select:none">Rule '+(i+1)+' &mdash; CAN '+hex+(r.id?' ('+r.id+')':'')+(r.mux>=0?' mux='+r.mux:'')+(peBusLabel(r.bus)?' '+peBusLabel(r.bus):'')+' &middot; '+r.ops.length+' op'+(r.ops.length===1?'':'s')+'</summary>'+
    '<div style="display:flex;gap:6px;margin:8px 0;flex-wrap:wrap">'+
      '<input class="sniff-input" style="width:110px" value="'+(r.id?('0x'+(r.id|0).toString(16).toUpperCase()):'')+'" placeholder="CAN / 0x7FF" onchange="peUpdateField('+i+',-1,\'id\',this.value)">'+
      '<input class="sniff-input" style="width:100px" type="number" min="-1" max="255" value="'+r.mux+'" placeholder="mux (-1=any)" onchange="peUpdateField('+i+',-1,\'mux\',this.value)">'+
      '<input class="sniff-input" style="width:82px" value="0x'+((muxMask||0)&255).toString(16)+'" placeholder="mux mask" title="mux mask, e.g. 0x7, 0xf, 0xff" onchange="peUpdateField('+i+',-1,\'mux_mask\',this.value)">'+
      '<input class="sniff-input" style="width:96px" value="'+peBusLabel(r.bus)+'" placeholder="bus" title="CH, VEH, PARTY, or comma list" onchange="peUpdateField('+i+',-1,\'bus\',this.value)">'+
      '<input class="sniff-input" style="width:58px" type="number" min="0" max="7" value="'+(r.match_byte||0)+'" title="match byte index; mask 0 disables" onchange="peUpdateField('+i+',-1,\'match_byte\',this.value)">'+
      '<input class="sniff-input" style="width:76px" value="0x'+((r.match_mask||0)&255).toString(16)+'" placeholder="match mask" title="match mask; 0 disables" onchange="peUpdateField('+i+',-1,\'match_mask\',this.value)">'+
      '<input class="sniff-input" style="width:76px" value="0x'+((r.match_val||0)&255).toString(16)+'" placeholder="match val" title="match value" onchange="peUpdateField('+i+',-1,\'match_val\',this.value)">'+
      '<label style="font-size:11px;color:var(--tx3);display:flex;align-items:center;gap:4px"><input type="checkbox"'+(r.send?' checked':'')+' onchange="peUpdateField('+i+',-1,\'send\',this.checked)"> send</label>'+
      '<button class="sniff-btn" style="margin-left:auto" onclick="peRemoveRule('+i+')">Remove Rule</button>'+
    '</div>'+
    ops+
    '<div style="margin-top:6px;display:flex;gap:4px;flex-wrap:wrap">'+
      '<button class="sniff-btn" onclick="peAddOp('+i+',\'set_bit\')">+ set_bit</button>'+
      '<button class="sniff-btn" onclick="peAddOp('+i+',\'set_byte\')">+ set_byte</button>'+
      '<button class="sniff-btn" onclick="peAddOp('+i+',\'or_byte\')">+ or_byte</button>'+
      '<button class="sniff-btn" onclick="peAddOp('+i+',\'and_byte\')">+ and_byte</button>'+
      '<button class="sniff-btn" onclick="peAddOp('+i+',\'counter\')">+ counter</button>'+
      '<button class="sniff-btn" onclick="peAddOp('+i+',\'emit_periodic\')">+ emit_periodic</button>'+
      '<button class="sniff-btn" onclick="peAddOp('+i+',\'checksum\')">+ checksum</button>'+
    '</div>'+
  '</details>';
}
function peRender(){
  const el=$('pe-rules');
  if(!peState.rules.length){el.innerHTML='<div style="font-size:12px;color:var(--tx3);text-align:center;padding:12px;border:1px dashed var(--bd);border-radius:6px">No rules yet. Click &ldquo;+ Add Rule&rdquo; below.</div>';}
  else{el.innerHTML=peState.rules.map((r,i)=>peRuleBlock(i,r)).join('');}
  $('pe-count').textContent=peState.rules.length+' rule'+(peState.rules.length===1?'':'s');
  peUpdateRuleOptions();
  peRenderPreview();
  peUpdateTestPreview();
}
function peBuildObj(){
  const meta=peGetMeta();
  const obj={name:meta.name||'Untitled',version:meta.version||'1.0'};
  if(meta.author)obj.author=meta.author;
  obj.rules=peState.rules.map(r=>{
    const out={id:r.id|0};
    if(r.mux>=0)out.mux=r.mux|0;
    const muxMask=r.mux_mask===undefined?peDefaultMuxMask(r.mux):r.mux_mask;
    if(r.mux>=0&&muxMask&&muxMask!==peDefaultMuxMask(r.mux))out.mux_mask=muxMask|0;
    if(peBusLabel(r.bus))out.bus=peBusLabel(r.bus);
    if(pluginRuleMatchMask(r)){out.match_byte=(r.match_byte||0)|0;out.match_mask=(r.match_mask||0)&255;out.match_val=(r.match_val||0)&255;}
    if(r.send===false)out.send=false;
    out.ops=r.ops.map(op=>{
      const o={type:op.type};
      if(op.type==='set_bit'){o.bit=op.bit|0;o.val=op.val?1:0;}
      else if(op.type==='set_byte'){o.byte=op.byte|0;o.val=(op.val|0)&255;if(op.mask!==undefined&&op.mask!==255)o.mask=op.mask|0;}
      else if(op.type==='or_byte'||op.type==='and_byte'){o.byte=op.byte|0;o.val=(op.val|0)&255;}
      else if(op.type==='counter'){o.byte=op.byte|0;o.mask=(op.mask===undefined?15:op.mask)|0;o.step=op.step||1;}
      else if(op.type==='emit_periodic'){o.interval=op.interval||100;if(op.gtw_silent)o.gtw_silent=true;}
      return o;
    });
    return out;
  });
  return obj;
}
function peRenderPreview(){$('pe-preview').textContent=JSON.stringify(peBuildObj(),null,2);}
function peFormatBytes(bytes){return(bytes||[]).slice(0,8).map(b=>toHex((b||0)&255,2)).join(' ');}
function peUpdateTestPreview(){
  const el=$('pe-test-preview');if(!el)return;
  if(!peState.rules.length){el.textContent='Add a rule to preview a test frame.';peSetTestStatus('Idle','');return;}
  const idx=parseInt($('pe-test-rule').value,10);
  if(isNaN(idx)||idx<0||idx>=peState.rules.length){el.textContent='Select a rule to test.';return;}
  const count=peParseInt($('pe-test-count').value,1),interval=peParseInt($('pe-test-interval').value,100);
  if(isNaN(count)||count<1||count>200){el.textContent='Count must be 1-200.';return;}
  if(isNaN(interval)||interval<10||interval>5000){el.textContent='Interval must be 10-5000 ms.';return;}
  const rule=peState.rules[idx];
  el.textContent='Preview '+peRuleLabel(rule,idx)+'\nWait for next matching bus frame, then apply this rule.\nInject '+count+'x every '+interval+' ms';
}
function peStopTestPoll(){if(peTestPollTimer){clearInterval(peTestPollTimer);peTestPollTimer=null;}}
async function pePollTestStatus(){
  try{
    const r=await fetch('/plugin_test_status');const d=await r.json();
    if(d.waiting){
      $('pe-test-preview').textContent='Waiting for CAN 0x'+toHex((d.targetId||d.id||0)&0x7FF,3)+'\nThe next matching bus frame will be modified and injected.\nProgress: 0/'+(d.total||0);
    }else if(d.id||d.data){
      $('pe-test-preview').textContent='Test CAN 0x'+toHex((d.id||0)&0x7FF,3)+'\nFrame: '+peFormatBytes(d.data||[])+(d.total?'\nProgress: '+d.sent+'/'+d.total:'');
    }
    if(d.active){
      peSetTestStatus(d.waiting?('Waiting for CAN 0x'+toHex((d.targetId||d.id||0)&0x7FF,3)):('Running '+d.sent+'/'+d.total+' · every '+d.interval+' ms'),'acc');
    }else{
      peSetTestStatus(d.total?(d.sent<d.total?'Stopped '+d.sent+'/'+d.total:'Done '+d.sent+'/'+d.total):'Idle',d.total&&d.sent>=d.total?'ok':'');
      peStopTestPoll();
    }
  }catch(e){}
}
async function peLoadInstalledPlugin(idx){
  const p=installedPlugins[idx];if(!p)return;
  if(peHasContent()&&!await dashConfirm('Load installed plugin into the editor? Current editor contents will be replaced.','Load plugin','Load'))return;
  $('pe-name').value=p.name||'';$('pe-author').value=p.author||'';$('pe-version').value=p.version||'1.0';
  peState={rules:(p.details||[]).map(r=>({id:r.id|0,mux:typeof r.mux==='number'?r.mux:-1,mux_mask:typeof r.mux_mask==='number'?r.mux_mask:peDefaultMuxMask(typeof r.mux==='number'?r.mux:-1),bus:peBusLabel(r.bus),match_byte:Math.max(0,Math.min(7,(typeof r.match_byte==='number'?r.match_byte:0)|0)),match_mask:((typeof r.match_mask==='number'?r.match_mask:0)|0)&255,match_val:((typeof r.match_val==='number'?r.match_val:0)|0)&255,send:r.send!==false,ops:(r.ops||[]).map(op=>{const out={type:op.type};if(op.type==='set_bit'){out.bit=op.bit|0;out.val=op.val?1:0;}else if(op.type==='set_byte'){out.byte=op.byte|0;out.val=(op.val|0)&255;out.mask=((typeof op.mask==='number'?op.mask:255)|0)&255;}else if(op.type==='or_byte'||op.type==='and_byte'){out.byte=op.byte|0;out.val=(op.val|0)&255;}else if(op.type==='counter'){out.byte=op.byte|0;out.mask=((typeof op.mask==='number'?op.mask:15)|0)&255;out.step=Math.max(1,((typeof op.step==='number'?op.step:1)|0)&255);}else if(op.type==='emit_periodic'){out.interval=Math.max(10,Math.min(5000,(typeof op.interval==='number'?op.interval:100)|0));out.gtw_silent=!!op.gtw_silent;}return out;})}))};
  peLoadedPluginName=p.name||'';peStopTestPoll();peSetTestStatus('Idle','');peRender();peSetStatus('Loaded "'+p.name+'" into editor','ok');
  $('pe-name').scrollIntoView({behavior:'smooth',block:'center'});
}
function peValidate(){
  const meta=peGetMeta();
  if(!meta.name)return 'Plugin name required';
  if(meta.name.length>31)return 'Name too long (max 31)';
  if(!peState.rules.length)return 'Add at least one rule';
  for(let i=0;i<peState.rules.length;i++){
    const r=peState.rules[i];
    if(!r.id||r.id<1||r.id>2047)return 'Rule '+(i+1)+': CAN ID must be 1-2047';
    if(r.mux<-1||r.mux>255)return 'Rule '+(i+1)+': mux must be -1..255';
    if(r.mux>=0&&(r.mux_mask<1||r.mux_mask>255))return 'Rule '+(i+1)+': mux mask must be 1-255';
    if(r.match_byte<0||r.match_byte>7)return 'Rule '+(i+1)+': match byte must be 0-7';
    if(r.match_mask<0||r.match_mask>255)return 'Rule '+(i+1)+': match mask must be 0-255';
    if(r.match_val<0||r.match_val>255)return 'Rule '+(i+1)+': match value must be 0-255';
    if(!r.ops.length)return 'Rule '+(i+1)+': add at least one op';
    for(let j=0;j<r.ops.length;j++){
      const op=r.ops[j];
      if(op.type==='set_bit'){if(op.bit<0||op.bit>63)return 'Rule '+(i+1)+' op '+(j+1)+': bit must be 0-63';}
      else if(op.type==='set_byte'||op.type==='or_byte'||op.type==='and_byte'){
        if(op.byte<0||op.byte>7)return 'Rule '+(i+1)+' op '+(j+1)+': byte must be 0-7';
        if(op.val<0||op.val>255)return 'Rule '+(i+1)+' op '+(j+1)+': val must be 0-255';
      }else if(op.type==='counter'){
        if(op.byte<0||op.byte>7)return 'Rule '+(i+1)+' op '+(j+1)+': byte must be 0-7';
        if(op.mask<1||op.mask>255)return 'Rule '+(i+1)+' op '+(j+1)+': mask must be 1-255';
        if(op.step<1||op.step>255)return 'Rule '+(i+1)+' op '+(j+1)+': step must be 1-255';
      }else if(op.type==='emit_periodic'){
        if(r.id!==2047||r.mux!==3)return 'Rule '+(i+1)+' op '+(j+1)+': emit_periodic requires CAN 0x7FF mux 3';
        if(r.send===false)return 'Rule '+(i+1)+' op '+(j+1)+': emit_periodic requires Send enabled';
        if(op.interval<10||op.interval>5000)return 'Rule '+(i+1)+' op '+(j+1)+': interval must be 10-5000 ms';
      }else if(op.type!=='checksum'){
        return 'Rule '+(i+1)+' op '+(j+1)+': unsupported op';
      }
    }
  }
  return null;
}
async function peInstall(){
  const err=peValidate();
  if(err){peSetStatus(err,'err');return;}
  const obj=peBuildObj();
  try{const r=await fetch('/plugins');const d=await r.json();
    if(d.plugins&&d.plugins.some(p=>p.name===obj.name)&&obj.name!==peLoadedPluginName){
      if(!await dashConfirm('A plugin named "'+obj.name+'" already exists. Overwrite?','Overwrite plugin','Overwrite'))return;
    }
  }catch(e){}
  const beforeSig=pluginStateSignature(installedPlugins);
  peSetStatus('Installing...','acc');
  try{
    await fetchJsonWithTimeout('/plugin_upload',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(obj)},5000);
    peLoadedPluginName=obj.name;
    try{await refreshPluginsNow();}catch(e){await refreshPluginsAfterAction(beforeSig);}
    peSetStatus('Installed','ok');
  }catch(e){
    if(await refreshPluginsAfterAction(beforeSig)){
      peLoadedPluginName=obj.name;
      peSetStatus('Installed','ok');
    }else{peSetStatus(actionErrorMessage(e,'Connection error'),'err');}
  }
}
async function peStartTest(){
  if(!peState.rules.length){peSetTestStatus('Add a rule first','err');return;}
  const idx=parseInt($('pe-test-rule').value,10);
  if(isNaN(idx)||idx<0||idx>=peState.rules.length){peSetTestStatus('Select a valid rule','err');return;}
  const count=peParseInt($('pe-test-count').value,1),interval=peParseInt($('pe-test-interval').value,100);
  if(isNaN(count)||count<1||count>200){peSetTestStatus('Count must be 1-200','err');return;}
  if(isNaN(interval)||interval<10||interval>5000){peSetTestStatus('Interval must be 10-5000 ms','err');return;}
  peSetTestStatus('Starting...','acc');
  try{
    const r=await fetch('/plugin_test',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({plugin:peBuildObj(),rule:idx,count:count,interval:interval})});
    const d=await r.json();
    if(d.ok){
      $('pe-test-preview').textContent='Waiting for CAN 0x'+toHex((d.targetId||d.id||0)&0x7FF,3)+'\nThe next matching bus frame will be modified and injected.\nProgress: 0/'+(d.total||0);
      peSetTestStatus(d.active?('Waiting for CAN 0x'+toHex((d.targetId||d.id||0)&0x7FF,3)):'Done','acc');
      peStopTestPoll();peTestPollTimer=setInterval(pePollTestStatus,500);pePollTestStatus();
    }else{
      peSetTestStatus(d.error||'Test failed','err');
    }
  }catch(e){peSetTestStatus('Connection error','err');}
}
async function peStopTest(){
  try{
    const r=await fetch('/plugin_test_stop',{method:'POST'});const d=await r.json();
    peStopTestPoll();
    peSetTestStatus(d.total?(d.sent<d.total?'Stopped '+d.sent+'/'+d.total:'Done '+d.sent+'/'+d.total):'Idle',d.total&&d.sent>=d.total?'ok':'');
  }catch(e){peSetTestStatus('Connection error','err');}
}
function peDownload(){
  const err=peValidate();
  if(err){peSetStatus(err,'err');return;}
  const obj=peBuildObj();
  const blob=new Blob([JSON.stringify(obj,null,2)],{type:'application/json'});
  const url=URL.createObjectURL(blob);
  const a=document.createElement('a');a.href=url;a.download=(obj.name||'plugin').replace(/[^A-Za-z0-9_-]/g,'_').toLowerCase()+'.json';document.body.appendChild(a);a.click();document.body.removeChild(a);URL.revokeObjectURL(url);
  peSetStatus('Downloaded','ok');
}
async function peReset(){
  if(peState.rules.length&&!await dashConfirm('Discard current editor contents?','Discard changes','Discard'))return;
  peState={rules:[]};peLoadedPluginName='';peStopTestPoll();
  $('pe-name').value='';$('pe-author').value='';$('pe-version').value='1.0';
  peRender();peSetStatus('','');peSetTestStatus('Idle','');
}

dashboardPollTimers.push(setInterval(poll,2000));dashboardPollTimers.push(setInterval(loadWifiStatus,10000));dashboardPollTimers.push(setInterval(loadApStatus,10000));dashboardPollTimers.push(setInterval(loadWifiNetworks,30000));dashboardPollTimers.push(setInterval(loadGatewayStatus,10000));dashboardPollTimers.push(setInterval(loadGatewayBlocked,5000));dashboardPollTimers.push(setInterval(loadGatewayDns,15000));
initCardMinimizers();initSubsectionMinimizers();initSystemMonitor();positionCanDebugPanels();setCanDebugUi();updateHW4(1);updateProfileControls(1,0,true);updateSniffIdToggle();poll();
</script>
</body>
</html>
)HTML";
