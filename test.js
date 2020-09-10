var addon = require('bindings')('hashint4.node')

console.log('This should be eight:', addon.hashInt4(1024))