import type { Hono } from 'hono';
import type { UpgradeWebSocket } from 'hono/ws';

export const createWebSocketHandler = (
  router: Hono,
  upgradeWebSocket: UpgradeWebSocket,
) => {
  router.get(
    '/ws',
    upgradeWebSocket((c) => {
      return {
        onMessage(event, ws) {
          console.log(`Message from client: ${event.data}`);
          ws.send('Hello from server!');
        },
        onClose: () => {
          console.log('Connection closed');
        },
      };
    }),
  );
};
