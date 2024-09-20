import { env } from './lib/env';
import localtunnel from 'localtunnel';

const tunnel = await localtunnel({ port: env.PORT });
console.log(`Server exposed at ${tunnel.url}`);
